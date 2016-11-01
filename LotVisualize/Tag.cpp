#include "header.h"

Tag::Tag() = default;

Tag::Tag(string _thisName, string _nextName)
    :thisName(_thisName), nextName(_nextName){}

Tag& Tag::operator=(const Tag& rhs){
    thisName = rhs.thisName;
    nextName = rhs.nextName;
    return *this;
}

string Tag::getThisName() const{
    return thisName;
}

string Tag::getNextName() const{
    return nextName;
}