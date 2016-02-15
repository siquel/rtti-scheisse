#pragma once
#include <cstdlib>
#include "class.h"
namespace rtti {

	enum class SeekPosition : size_t {
		/// From begin
		Begin = 0,
		/// From current position
		Current = 1,
		/// From end
		End = 2
	};

	class MemoryStream {
	private:
		size_t dataSize;
		size_t position;
		size_t elements;
		unsigned char* buffer;

	public:
		MemoryStream()
			: dataSize(32u), buffer(nullptr), position(0u), elements(0u) {
			buffer = static_cast<unsigned char*>(std::realloc(buffer, dataSize));
		}

		~MemoryStream() {
			free(buffer);
		}

		size_t MemoryStream::read(unsigned char* outBuffer, const size_t size)  {
			std::memcpy(outBuffer, buffer + position, size);
			position += size;
			return size;
		}


		size_t MemoryStream::write(const unsigned char* data, const size_t size)  {
			if ((position + size) >= dataSize) {
				dataSize = (dataSize)* 2u + size;
				buffer = static_cast<unsigned char*>(std::realloc(buffer, dataSize));
			}
			std::memcpy(buffer + position, data, size);
			elements += size;
			position += size;
			return size;
		}

		void MemoryStream::seek(const SeekPosition seekpos, const long offset)  {
			if (seekpos == SeekPosition::Begin) {
				position = offset;
			}
			else if (seekpos == SeekPosition::End) {
				position = size() + offset;
			}
			else {
				position += offset;
			}
		}

		size_t MemoryStream::size()  {
			return elements;
		}
	};

	template <class T>
	void generateSerializable(const std::string& className, const T* self, MemoryStream& to) {
		Class* clazz = Class::classForName(className);
		assert(clazz != nullptr);
		assert(self != nullptr);
		size_t count;
		rtti::RTTIFieldDescriptor** fields = clazz->getFields(&count);
		assert(fields != nullptr);
		size_t n = className.size();
		to.write((unsigned char*)&n, sizeof(size_t));
		to.write((const unsigned char*)className.c_str(), className.size());

		for (size_t i = 0; i < count; ++i) {
			RTTIFieldDescriptor* field = fields[i];
			const std::string& name = field->getName();
			n = name.size();
			to.write((unsigned char*)&n, sizeof(size_t));
			to.write((const unsigned char*)name.c_str(), name.size());
			void* buffer[1024] = { 0 };

			auto type = field->getType();
			int tag = type->getTag();
			to.write((unsigned char*)&tag, sizeof(int));
			field->getValue((void*)self, buffer);
			to.write((unsigned char*)buffer, field->getSize());
		}
	}
}