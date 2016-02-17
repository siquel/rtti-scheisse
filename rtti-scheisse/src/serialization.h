#pragma once
#include <cstdlib>
#include "class.h"
namespace rtti {
	using uint32 = unsigned int;
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using int64 = long long;
	using uint64 = unsigned long long;
	enum class SeekPosition : size_t {
		/// From begin
		Begin = 0,
		/// From current position
		Current = 1,
		/// From end
		End = 2
	};
	class Stream {
	public:
		virtual size_t read(unsigned char* outBuffer, const size_t size) = 0;
		virtual size_t write(const unsigned char* data, const size_t size) = 0;
		virtual void seek(const SeekPosition seekpos, const long offset) = 0;
		virtual size_t size() = 0;
	};
	class MemoryStream : public Stream {
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

	class BinaryWriter {
	private:
		Stream* stream;
	public:
		BinaryWriter(Stream* stream) : stream(stream) {
		}

		~BinaryWriter() {
		}

		void write(unsigned char value) {
			stream->write((unsigned char*)&value, sizeof(unsigned char));
		}

		void write(unsigned short value) {
			stream->write((unsigned char*)&value, sizeof(unsigned short));
		}

		void write(unsigned int value) {
			stream->write((unsigned char*)&value, sizeof(unsigned int));
		}

		void write(uint64 value) {
			stream->write((unsigned char*)&value, sizeof(uint64));
		}

		void write(char value) {
			stream->write((unsigned char*)&value, sizeof(char));
		}

		void write(short value) {
			stream->write((unsigned char*)&value, sizeof(short));
		}

		void write(int value) {
			stream->write((unsigned char*)&value, sizeof(int));
		}

		void write(int64 value) {
			stream->write((unsigned char*)&value, sizeof(int64));
		}

		void write(float value) {
			stream->write((unsigned char*)&value, sizeof(float));
		}

		void write(double value) {
			stream->write((unsigned char*)&value, sizeof(double));
		}

		void write(const std::string& value) {
			write7BitEncodedInt(value.size());
			stream->write((unsigned char*)value.c_str(), sizeof(char) * value.size());
		}

		void write7BitEncodedInt(unsigned long long value) {

			int index = 3;
			bool reached = false;
			uint64 mask = 0x7Fu << (index * 7);

			while (index >= 0) {
				uint64 val = (mask & value);

				if (val > 0 || reached) {

					reached = true;

					val >>= index * 7;

					if (index > 0) val |= 0x80;

					char u8val = (char)val;

					stream->write((unsigned char*)&u8val, sizeof(char));
				}

				mask >>= 7;

				--index;
			}

			if (!reached && index < 0) {
				uint8 a = 0;

				stream->write(&a, sizeof(uint8));
			}
		}
	};
	class BinaryReader {
	private:
		Stream* stream;
	public:
	BinaryReader(Stream* stream)
		: stream(stream) {
		//assert(stream->)
	}

	~BinaryReader() {}

	unsigned short BinaryReader::readInt16() {
		return static_cast<unsigned short>(readUint16());
	}
	int BinaryReader::readInt32() {
		return static_cast<int>(readUint32());
	}
	long BinaryReader::readInt64() {
		return static_cast<long>(readUint64());
	}

	unsigned short BinaryReader::readUint16() {
		unsigned char b1 = readByte();
		unsigned char b2 = readByte();
		return uint16(b1) | uint16(b2) << 8;
	}
	unsigned int BinaryReader::readUint32() {
		unsigned char b1 = readByte();
		unsigned char b2 = readByte();
		unsigned char b3 = readByte();
		unsigned char b4 = readByte();
		return unsigned int(b1) | uint32(b2) << 8 |
			uint32(b3) << 16 | uint32(b4) << 24;
	}
	uint64 BinaryReader::readUint64() {
		unsigned char b1 = readByte();
		unsigned char b2 = readByte();
		unsigned char b3 = readByte();
		unsigned char b4 = readByte();
		unsigned char b5 = readByte();
		unsigned char b6 = readByte();
		unsigned char b7 = readByte();
		unsigned char b8 = readByte();
		return uint64(b1) | uint64(b2) << 8 |
			uint64(b3) << 16 | uint64(b4) << 24 |
			uint64(b5) << 32 | uint64(b6) << 40 |
			uint64(b7) << 48 | uint64(b8) << 56;
	}

	char BinaryReader::readChar() {
		return static_cast<char>(readByte());
	}

	unsigned char BinaryReader::readByte() {
		unsigned char buffer[1];
		stream->read(buffer, 1);
		return static_cast<unsigned char>(buffer[0]);
	}

	float BinaryReader::readSingle()  {
		uint32 val = readUint32();
		return *(float*)&val;
	}

	double BinaryReader::readDouble()  {
		uint64 val = readUint64();
		return *(double*)&val;
	}

	std::string BinaryReader::readString() {
		uint64 size = read7BitEncodedInt();
		std::string str;
		str.reserve(static_cast<uint32>(size));
		size_t index = 0;
		while (index++ < size) {
			str.append(1, readChar());
		}
		return str;
	}

	uint64 BinaryReader::read7BitEncodedInt() {
		uint64 buffer = 0;
		int index = 0;
		unsigned char current = 0;

		do {
			if (index++ == 8)
				throw std::runtime_error("Could not read variable-length quantity from provided stream");
			buffer <<= 7;
			current = readByte();
			buffer |= (current & 0x7Fu);
		} while ((current & 0x80) != 0);

		return buffer;
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
		BinaryWriter writer(&to);
		writer.write(className);
		writer.write7BitEncodedInt(count);
		for (size_t i = 0; i < count; ++i) {
			RTTIFieldDescriptor* field = fields[i];
			const std::string& name = field->getName();
			writer.write(name);
			void* buffer[1024] = { 0 };

			auto type = field->getType();
			int tag = type->getTag();
			to.write((unsigned char*)&tag, sizeof(int));
			field->getValue((void*)self, buffer);
			to.write((unsigned char*)buffer, field->getSize());
		}
	}

	void* deserialize(MemoryStream& from) {
		BinaryReader reader(&from);
		std::string className = reader.readString();
		uint64 count = reader.read7BitEncodedInt();
		//className.resize(std::atoi())
		return nullptr;
	}
}