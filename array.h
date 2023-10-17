#include <iostream>

class Array {
public:
    Array(std::ostream &ostream)
            : Ostream_(ostream), size_(0), capacity_(2), data_(new int[capacity_]) {
        Ostream_ << "Constructed. " << *this << std::endl;

    }

    Array(const Array &array)
            : Ostream_(array.Ostream_), size_(array.size_), capacity_(array.capacity_),
              data_(new int[array.capacity_]) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = array.data_[i];
        }
        Ostream_ << "Constructed from another Array. " << *this << std::endl;

    }

    Array(size_t size, std::ostream &ostream = std::cout, int defaultValue = 0)
            : Ostream_(ostream), size_(size), capacity_(size * 2), data_(new int[capacity_]) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = defaultValue;
        }
        Ostream_ << "Constructed with default. " << *this << std::endl;

    }

    ~Array() {
        Ostream_ << "Destructed " << size_ << std::endl;
        delete[] data_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity > capacity_) capacity_ = newCapacity;
    }

    void Resize(size_t newSize) {
        if (newSize > capacity_) {
            capacity_ = newSize;
            int *const NewData = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                NewData[i] = data_[i];
            }
            delete[] data_;
            data_ = NewData;
        }
        size_ = newSize;
    }

    void PushBack(int value = 0) {
        if (size_ >= capacity_) {
            capacity_ *= 2;
            int *const NewData = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                NewData[i] = data_[i];
            }
            delete[] data_;
            data_ = NewData;
        }

        data_[size_] = value;
        size_++;
    }

    void PopBack() {
        --size_;
    }

    const int &operator[](const size_t i) const {
        return const_cast<Array *>(this)->operator[](i);
    }

    int &operator[](const size_t i) {
        return data_[i];
    }

    explicit operator bool() const {
        return size_ != 0;
    }

    bool operator<(const Array &it) const {
        if (size_ < it.size_) {
            for (size_t i = 0; i < size_; ++i) {
                if (data_[i] < it.data_[i]) return true;
                else if (data_[i] > it.data_[i]) return false;
            }
            return true;
        } else {
            for (size_t i = 0; i < it.size_; ++i) {
                if (data_[i] < it.data_[i]) return true;
                else if (data_[i] > it.data_[i]) return false;
            }
            return false;
        }
    }

    bool operator>(const Array &it) const {
        if (it < *this) return true;
        return false;
    }


    bool operator!=(const Array &it) const {
        if (*this == it) return false;
        return true;
    }

    bool operator==(const Array &it) const {
        if (it < *this || *this < it) return false;
        return true;
    }

    bool operator<=(const Array &it) const {
        if (*this < it || *this == it) return true;
        return false;
    }

    bool operator>=(const Array &it) const {
        if (*this > it || *this == it) return true;
        return false;
    }

    Array &operator<<(const int value) {
        PushBack(value);
        return *this;
    }

    Array &operator<<(const Array &it) {
        for (size_t i = 0; i < it.size_; ++i) {
            PushBack(it.data_[i]);
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Array &array);

private:
    std::ostream &Ostream_;
    size_t size_, capacity_;
    int *data_;
    // ...
};

std::ostream &operator<<(std::ostream &ostream, const Array &array) {
    ostream << "Result Array's capacity is " << array.capacity_ << ' ';
    size_t size = array.size_;
    if (size == 0) {
        ostream << "and size is " << size;
    } else {
        ostream << "and size is " << size << ", elements are: ";
        for (size_t i = 0; i < size - 1; ++i) {
            ostream << array.data_[i] << ", ";
        }
        ostream << array.data_[size - 1];
    }
    return ostream;
}


