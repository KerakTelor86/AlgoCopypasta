#!/bin/env python3
import os

SOURCE = './source'

def get_name(filename):
    return filename.split('_')[1]

if __name__ == '__main__':
    sections = sorted(os.listdir(SOURCE))
    for section in sections:
        path = SOURCE + '/' + section
        print("\\section{%s}" % get_name(section))
        files = sorted(os.listdir(SOURCE + '/' + section))
        for file in files:
            full_path = path + '/' + file
            if os.path.isfile(full_path):
                name, ext = os.path.splitext(file)
                print("\\subsection{%s}" % get_name(name))
                if ext == '.tex':
                    print("\\input{%s}" % full_path)
                elif ext == '.txt':
                    print("\\lstinputlisting{%s}" % full_path)
                elif ext == '.cpp':
                    print("\\lstinputlisting[language=c++]{%s}" % full_path)
