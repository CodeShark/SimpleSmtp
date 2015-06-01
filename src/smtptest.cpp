///////////////////////////////////////////////////////////////////////////////
//
// smtptest.cpp
//
// Copyright (c) 2015 Eric Lombrozo
//
// All Rights Reserved.

#include <iostream>

#include "smtp.h"

using namespace std;

class Options
{
public:
    Options() : verify_(true), verbose_(false) { }

    int process(int argc, char* argv[]);

    bool verify() const { return verify_; }
    bool verbose() const { return verbose_; }

private:
    bool verify_;
    bool verbose_;
};

int Options::process(int argc, char* argv[])
{
    int i = 1;
    for (; (i < 3) && (i < argc); i++)
    {
        if (string(argv[i]) == "-k")        { verify_ = false; }
        else if (string(argv[i]) == "-v")   { verbose_ = true; }
    }
    return i;
}

int main(int argc, char* argv[])
{
    Options options;
    int i = options.process(argc, argv);

    int nArgs = argc - i;
    if (nArgs < 7 || nArgs > 9)
    {
        cerr << "# Usage: " << argv[0] << " [options] <username> <password> <url> <subject> <body> <from> <to> [cc] [bcc]" << endl;
        cerr << "# Options:" << endl;
        cerr << "#   -k do not verify certificate" << endl;
        cerr << "#   -v verbose" << endl;
        return -1;
    }

    try
    {

        SmtpTls smtp(argv[i], argv[i+1], argv[i+2]);
        smtp.setSubject(argv[i+3]);
        smtp.setBody(argv[i+4]);
        smtp.setFrom(argv[i+5]);
        smtp.addTo(argv[i+6]);
        if (nArgs > 7) { smtp.addCc(argv[i+7]);  }
        if (nArgs > 8) { smtp.addBcc(argv[i+8]); }

        smtp.send(options.verify(), options.verbose());
        cout << "Sent." << endl;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return -2;
    }

    return 0;
}
