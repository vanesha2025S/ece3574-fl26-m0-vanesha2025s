#include "Document.hpp"
#include <fstream>
#include <sstream>

Document::Document(std::string title, std::string contents) {
    title_ = title;
    contents_ = contents;
}

bool Document::operator==(const Document& other) const {
    return title_ == other.title_
        && sourcePath_ == other.sourcePath_
        && contents_ == other.contents_;
}

bool Document::operator!=(const Document& other) const {
    return !(*this == other);
}

bool Document::load(const std::string& path) {
    //this is to open the file
    std::ifstream file(path);

    if (!file) {
        return false;
    }

    //this reads the entire file into a string
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();


    //this finds the last slash to find the filename
    std::size_t pos = path.find_last_of("/\\");

    // if there is no slash, the path itself is the filename
    if (pos == std::string::npos) {
        title_ = path;
    }
    else {
        title_ = path.substr(pos + 1);
    }

    //this updates the document after the file was successfully read
    sourcePath_ = path;
    contents_ = contents;

    return true;

}

const std::string& Document::title() const noexcept {
    return title_;

}

const std::string& Document::sourcePath() const noexcept {
    return sourcePath_;

}

const std::string& Document::contents() const noexcept {
    return contents_;
  
}

void Document::setTitle(std::string title) {
    title_ = title;
  
}

std::size_t Document::characterCount() const noexcept {
    return contents_.size();
    
}

bool Document::empty() const noexcept {
    return contents_.empty();
   
}
