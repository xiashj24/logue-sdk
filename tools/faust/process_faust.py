import re
import sys

def remove_functions_and_inheritance(file_path):
    with open(file_path, 'r') as file:
        code = file.read()

    # Comment out the buildUserInterface function
    code = re.sub(r'(void buildUserInterface\([^)]*\)\s*\{[^}]*\})', r'/* \1 */', code, flags=re.DOTALL)

    # Remove the metadata function
    code = re.sub(r'void metadata\([^)]*\)\s*\{[^}]*\}', '', code, flags=re.DOTALL)

    # Remove the "final : public dsp" inheritance
    code = re.sub(r'\bfinal\s*:\s*public\s*dsp\b', '', code)


    with open(file_path, 'w') as file:
        file.write(code)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    remove_functions_and_inheritance(file_path)