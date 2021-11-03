#pragma once

//
// Source:
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
// https://stackoverflow.com/a/24736796/11053404
// Author: Luca Davanzo
//

#include <map>
#include <string>

class MainOptions {
public:

    typedef std::pair<std::string, std::string> Option;

    MainOptions(int argc, char* argv[]) :
        argc_(argc),
        argv_(argv) {
        appName_ = argv_[0];
        this->parse();
    }

    virtual ~MainOptions() {
    }

    std::string getAppName() const {
        return appName_;
    }

    void printOptions() const {
        std::map<std::string, std::string>::const_iterator m = options_.begin();
        int i = 0;
        if (options_.empty()) {
            printf("No parameters\n");
        }
        for (; m != options_.end(); m++, ++i) {
            printf("Parameter [%i] [%s %s]\n", i, (*m).first.c_str(), (*m).second.c_str());
        }
    }

    bool hasKey(const std::string& key) const {
        return options_.find(key) != options_.end();
    }

    Option* getParamFromKey(
        const std::string& key) const {
        const Options::const_iterator i = options_.find(key);
        Option* o = 0;
        if (i != options_.end()) {
            o = new Option((*i).first, (*i).second);
        }
        return o;
    }
private:
    typedef std::map<std::string, std::string> Options;
    void parse() {
        typedef std::pair<std::string, std::string> Option;
        Option* option = new std::pair<std::string, std::string>();
        for (const char* const* i = this->begin() + 1; i != this->end(); i++) {
            const std::string p = *i;
            if (option->first == "" && p[0] == '-') {
                option->first = p;
                if (i == this->last()) {
                    options_.insert(Option(option->first, option->second));
                }
                continue;
            }
            else if (option->first != "" && p[0] == '-') {
                option->second = "null"; /* or leave empty? */
                options_.insert(Option(option->first, option->second));
                option->first = p;
                option->second = "";
                if (i == this->last()) {
                    options_.insert(Option(option->first, option->second));
                }
                continue;
            }
            else if (option->first != "") {
                option->second = p;
                options_.insert(Option(option->first, option->second));
                option->first = "";
                option->second = "";
                continue;
            }
        }
    }

    const char* const* begin() const {
        return argv_;
    }

    const char* const* end() const {
        return argv_ + argc_;
    }

    const char* const* last() const {
        return argv_ + argc_ - 1;
    }


    Options options_;
    int argc_;
    char** argv_;
    std::string appName_;
};