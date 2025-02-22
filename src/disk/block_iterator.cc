#include "disk/block_iterator.h"
#include "disk/block.h"
#include "common/option.h"
#include "util/util.h"
#include "type/key.h"

#include <iostream>
namespace koishidb {
    BlockIterator::BlockIterator(Block *block, const Option* opt) : data_(block->data), size_(block->size), cmp_(opt->cmp){
        SeekToFirst();
    }




    void BlockIterator::SeekToFirst() {
        offset_ = 0;
        key_.clear();
        value_ = Slice(data_, 0); // empty
    }

    void BlockIterator::Next() {
        //  next entry offset

        offset_ = value_.data() + value_.size() - data_;
        if (!this->Valid()) {
            return;
        }
        Slice rest_entries = Slice(data_ + offset_, size_ - offset_);
        uint32_t internal_key_len;
        GetVarint32(&rest_entries, &internal_key_len);
        key_ = std::string(rest_entries.data(), internal_key_len);
        rest_entries.Advance(internal_key_len);

        uint32_t  value_len;
        GetVarint32(&rest_entries, &value_len);
        value_ = Slice(rest_entries.data(), value_len);
    }

    // iff return true, the Iterator.Key() == target
    // seek can find the first entry >= target
    bool BlockIterator::Seek(const Slice &target) {
        SeekToFirst();
        // linear
        Next();
        while (Valid() && cmp_->Compare(Key(), target) == -1) {
            Next();
        }

        if (Valid() && cmp_->Compare(Key(), target) == 0) {
            return true;
        } else {
            return false;
        }
    }

    Slice BlockIterator::Key() const {
       return key_;
    }

    Slice BlockIterator::Value() const {
        return value_;
    }

    bool BlockIterator::Valid() const {
        return offset_ < size_;
    }

    void BlockIterator::Prev() {
        // empty
    }

    void BlockIterator::SeekToLast() {
        // To do
    }
};