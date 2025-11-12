from pathlib import Path

def main():
    try:
        print(Path(__file__).parent / "config.txt")
        config = open(Path(__file__).parent / "config.txt", 'r').read().splitlines()
    except:
        print("'config.txt' must be provided in the same directory as config_wizard.py.")
        exit(1)

    for (line_number, line) in enumerate(config):
        line = line.split("#")[0]
        line = line.split(":")
        
        #print(len(line) == 1, not line[0] == "")
        line_is_empty = len(line) == 1 and line[0] == ""
        if line_is_empty:
            continue

        if len(line) != 4:
            print("Invalid format on line " + str(line_number))
            exit(1)
        
        option_name = line[0].strip()
        option_description = line[1].strip()
        option_type = line[2].strip()
        option_default = line[3].strip()

        print(f'option({option_name} "{option_description}" {option_default}) {option_type}')

main()