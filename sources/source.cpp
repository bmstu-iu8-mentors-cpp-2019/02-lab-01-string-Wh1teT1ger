//Copyright 2020 Burylov Denis

#include <string.hpp>

void String::resize(size_t size) {
    char *newData = new char[size];
    for (size_t i = 0; i < Size_; i++) {
        newData[i] = Data[i];
    }
    delete[] Data;
    Size_ = size;
    Data = newData;
}

String::~String() {
    delete[] Data;
}

String::String() : Data(new char[0]), Size_(0) {}

String::String(const String &rhs) : Size_(rhs.Size_) {
    if (rhs.Data != nullptr) {
        Data = new char[Size_];
        for (size_t i = 0; i < Size_; i++) Data[i] = rhs.Data[i];
    }
}

String::String(const char *data) : Size_(0) {
    for (int i = 0; data[i] != '\0'; i++) Size_++;
    Data = new char[Size_];
    for (size_t i = 0; i < Size_; i++) Data[i] = data[i];
}

String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] Data;
        Size_ = rhs.Size_;
        Data = new char[Size_];
        for (size_t i = 0; i < Size_; i++) Data[i] = rhs.Data[i];
    }
    return *this;
}

String &String::operator+=(const String &rhs) {
    resize(rhs.Size_ + Size_);
    for (size_t i = Size_ - rhs.Size(); i < Size_; i++)
        Data[i] = rhs.Data[i - Size_ + rhs.Size_];
    return *this;
}

String &String::operator+=(const char *rhs) {
    String rh(rhs);
    resize(Size_ + rh.Size_);
    for (size_t i = Size_ - rh.Size_; i < Size_; i++)
        Data[i] = rhs[i - Size_ + rh.Size_];
    return *this;
}

String &String::operator*=(unsigned int m) {
    String a(*this);
    for (size_t i = 1; i < m; i++) *this += a;
    return *this;
}

bool String::operator==(const String &rhs) const {
    if (Size_ == rhs.Size_) {
        for (size_t i = 0; i < Size_; i++) {
            if (Data[i] != rhs.Data[i]) return false;
        }
        return true;
    } else {
        return false;
    }
}

bool String::operator<(const String &rhs) const {
    if (Size_ != rhs.Size_) return Size_ < rhs.Size_;
    for (size_t i = 0; i < Size_; i++) {
        if (Data[i] < rhs.Data[i]) return true;
        if (Data[i] > rhs.Data[i]) return false;
    }
    return false;
}

size_t String::Find(const String &substr) const {
    for (size_t i = 0; i < Size_; i++) {
        if (substr[0] == Data[i]) {
            for (size_t j = 0; j < substr.Size_; j++) {
                if (substr.Data[j] != Data[i + j]) break;
                if (j == substr.Size_ - 1) return i;
            }
        }
    }
    return -1;
}

size_t String::Find(const char *str) const {
    String substr(str);
    for (size_t i = 0; i < Size_; i++) {
        if (substr[0] == Data[i]) {
            for (size_t j = 0; j < substr.Size_; j++) {
                if (substr.Data[j] != Data[i + j]) break;
                if (j == substr.Size_ - 1) return i;
            }
        }
    }
    return -1;
}

void String::Replace(char oldSymbol, char newSymbol) {
    for (size_t i = 0; i < Size_; i++) {
        if (Data[i] == oldSymbol) Data[i] = newSymbol;
    }
}

size_t String::Size() const {
    return Size_;
}

bool String::Empty() const {
    return Size_ == 0;
}

char String::operator[](size_t index) const {
    return Data[index];
}

char &String::operator[](size_t index) {
    return Data[index];
}

void String::RTrim(char symbol) {
    size_t count = 0;
    for (size_t i = Size_; i > 0; i--) {
        if (Data[i - 1] == symbol) {
            count++;
        } else {
            break;
        }
    }
    Size_ = Size_ - count;
    char *newData = new char[Size_];
    for (size_t i = 0; i < Size_; i++) {
        newData[i] = Data[i];
    }
    delete[] Data;
    Data = newData;
}

void String::LTrim(char symbol) {
    size_t count = 0;
    for (size_t i = 0; i < Size_; i++) {
        if (Data[i] == symbol) {
            count++;
        } else {
            break;
        }
    }
    Size_ = Size_ - count;
    char *newData = new char[Size_];
    for (size_t i = 0; i < Size_; i++) {
        newData[i] = Data[i + count];
    }
    delete[] Data;
    Data = newData;
}

void String::swap(String &oth) {
    String newString = oth;
    oth = *this;
    *this = newString;
}

String operator+(const String &a, const String &b) {
    String newString;
    newString += a;
    newString += b;
    return newString;
}

String operator*(const String &a, unsigned int b) {
    String newString;
    for (unsigned int i = 0; i < b; i++) {
        newString += a;
    }
    return newString;
}

bool operator!=(const String &a, const String &b) {
    if (a.Size_ == b.Size_) {
        for (size_t i = 0; i < a.Size_; i++) {
            if (a.Data[i] != b.Data[i]) return true;
        }
        return false;
    } else {
        return true;
    }
}

bool operator>(const String &a, const String &b) {
    if (a.Size_ != b.Size_) return a.Size_ > b.Size_;
    for (size_t i = 0; i < a.Size_; i++) {
        if (a.Data[i] > b.Data[i]) return true;
        if (a.Data[i] < b.Data[i]) return false;
    }
    return false;
}

std::ostream &operator<<(std::ostream &out, const String &str) {
    for (size_t i = 0; i < str.Size_; i++) {
        out << str[i];
    }
    return out;
}

bool operator==(const char *a, const String &b) {
    size_t size = 0;
    for (size_t i = 0; a[i] != '\0'; i++) size++;
    if (b.Size_ == size) {
        for (size_t i = 0; i < size; i++) {
            if (b[i] != a[i]) return false;
        }
        return true;
    } else {
        return false;
    }
}
