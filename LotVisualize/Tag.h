#pragma once

class Tag{
public:
    string thisName;
    string nextName;

public:
    Tag();
    Tag(string _thisName, string _nextName);
    Tag& operator=(const Tag& tag);
};