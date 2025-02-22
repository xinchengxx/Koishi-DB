#ifndef KOISHIDB_SRC_INCLUDE_COMMON_COMMON_H
#define KOISHIDB_SRC_INCLUDE_COMMON_COMMON_H

#include <cstddef>
#include <cstdint>

// this file defines the constant that may be used in other files
namespace koishidb {
    // enum class, specify one byte
    enum class KeyType: uint8_t {
        kTypeValue = 0x01,
        kTypeDeletion = 0x02,
    };

    using SequenceNumber = uint64_t;

    constexpr KeyType kTypeSeek = KeyType::kTypeValue;
    // constant here
    constexpr int kSkipListNodeMaxLevel = 20;
    constexpr int kMemtableMaxSize = 4096; // max mutable memtable size
    constexpr int kWriteBatchHeader = 12;
    constexpr int kL0MaxFiles = 10;// should be modified later
    constexpr int kMaxMemtableSize = 4096;
    constexpr int kBlockSize = 4096; // one block size;
    constexpr int kWritableFileBuffer = 65536; // Buffer;
    constexpr int kBloomFilterPerKeySize = 10; //
    constexpr int kFilterBaseLg = 11;
    constexpr int kFilterBase = 1 << kFilterBaseLg;
    constexpr int kFixedFooterSize = 40;
    constexpr int kManifestReserved = 2048;
};

#endif