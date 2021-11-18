#!/bin/bash
cd source
for dir in *; do
    for file in "$dir/*.cpp"; do
        astyle --style=java --indent=spaces=2 --pad-oper --pad-comma \
        --delete-empty-lines --align-pointer=type --align-reference=type \
        --remove-braces --convert-tabs --max-code-length=80 \
        --indent-namespaces --lineend=linux --unpad-paren --suffix=none \
        --formatted "$file" --options=none &> /dev/null
    done
done
cd ..
