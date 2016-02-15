#pragma once
#include <cstdlib>
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
}