#pragma once

///
/// \brief Custom utility gl exception classes.
///

#include <exception>
#include <stdexcept>
#include <string>

namespace ge {

///
/// \brief The Error class is the base class for all game engine exceptions/errors.
///
class Error : public std::exception {
public:
    explicit Error(const std::string &whatArg) : whatArg(whatArg){}
    virtual const char* what() const noexcept override {return this->whatArg.c_str();}

private:
    std::string whatArg;
};

///
/// \brief The WindowingSystemError class deals with error in the windowing system.
///
class WindowingSystemError : public Error {
public:
    explicit WindowingSystemError(const std::string &whatArg) : Error(whatArg) {}
};

///
/// \brief The GlExtensionLoadingError class deals with errors in loading OpenGL extensions.
///
class GlExtensionLoadingError : public Error {
public:
    explicit GlExtensionLoadingError(const std::string &whatArg) : Error(whatArg) {}
};

///
/// \brief The BuildError class deals with errors that may occur when compiling/linking shaders.
///
class BuildError : public Error {
public:
    explicit BuildError(const std::string &whatArg) : Error(whatArg){}
};

///
/// \brief The LoadError class deals with errors that may occur when loading files
///
class LoadError : public Error {
public:
    explicit LoadError(const std::string &whatArg) : Error(whatArg) {}
};
} // namespace ge
