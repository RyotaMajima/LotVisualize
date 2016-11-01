#pragma once

class Tag{
private:
    string thisName;
    string nextName;

public:
    Tag();
    Tag(string _thisName, string _nextName);
    Tag& operator=(const Tag& tag);
    string getThisName() const;
    string getNextName() const;
};