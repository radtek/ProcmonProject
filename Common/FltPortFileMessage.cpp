#include "FltPortFileMessage.hpp"

KmUmShared::FileMessage::FileMessage(
    MessageCode MessageCode,
    unsigned __int64 Timestamp,
    unsigned __int32 ProcessId,
    const unsigned __int8* String1Buffer,
    unsigned __int32 String1BufferSize,
    long Status
) : messageCode{MessageCode},
    timestamp{Timestamp},
    processId{ProcessId},
    string1{String1Buffer, String1BufferSize},
    status{Status}
{
}

Cpp::Stream & KmUmShared::FileMessage::Serialize(Cpp::Stream & Stream) const
{
    Stream << FilterMessageHeader{ messageCode }
        << string1
        << timestamp
        << processId
        << status;

    return Stream;
}

Cpp::Stream & KmUmShared::FileMessage::Deserialize(Cpp::Stream & Stream)
{
    Stream >> string1
        >> timestamp
        >> processId
        >> status;

    return Stream;
}

KmUmShared::FileCreateMessage::FileCreateMessage(
    unsigned __int64 Timestamp, 
    unsigned __int32 ProcessId, 
    const unsigned __int8 * String1Buffer, 
    unsigned __int32 String1BufferSize,
    long Status
) : FileMessage(MessageCode::msgFileCreate, Timestamp, ProcessId, String1Buffer, String1BufferSize, Status)
{
}

Cpp::Stream & KmUmShared::operator<<(Cpp::Stream & Stream, const FileCreateMessage & FileCreateMessage)
{
    return FileCreateMessage.Serialize(Stream);
}

Cpp::Stream & KmUmShared::operator>>(Cpp::Stream & Stream, FileCreateMessage & FileCreateMessage)
{
    return FileCreateMessage.Deserialize(Stream);
}

Cpp::Stream & KmUmShared::operator<<(Cpp::Stream & Stream, const FileCloseMessage & FileCloseMessage)
{
    return FileCloseMessage.Serialize(Stream);
}

Cpp::Stream & KmUmShared::operator >> (Cpp::Stream & Stream, FileCloseMessage & FileCloseMessage)
{
    return FileCloseMessage.Deserialize(Stream);
}

Cpp::Stream & KmUmShared::operator<<(Cpp::Stream & Stream, const FileCleanupMessage & FileCleanupMessage)
{
    return FileCleanupMessage.Serialize(Stream);
}

Cpp::Stream & KmUmShared::operator >> (Cpp::Stream & Stream, FileCleanupMessage & FileCleanupMessage)
{
    return FileCleanupMessage.Deserialize(Stream);
}

KmUmShared::FileCloseMessage::FileCloseMessage(
    unsigned __int64 Timestamp,
    unsigned __int32 ProcessId,
    const unsigned __int8 * String1Buffer,
    unsigned __int32 String1BufferSize,
    long Status
) : FileMessage(MessageCode::msgFileClose, Timestamp, ProcessId, String1Buffer, String1BufferSize, Status) 
{
}

KmUmShared::FileCleanupMessage::FileCleanupMessage(
    unsigned __int64 Timestamp,
    unsigned __int32 ProcessId,
    const unsigned __int8 * String1Buffer,
    unsigned __int32 String1BufferSize,
    long Status
) : FileMessage(MessageCode::msgFileCleanup, Timestamp, ProcessId, String1Buffer, String1BufferSize, Status) 
{
}