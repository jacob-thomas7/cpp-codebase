from pathlib import Path

SWITCH = { "ON", "OFF" }

BUILD_VARS = {
    "CORE_STATIC" : SWITCH,
    "CORE_SHARED" : SWITCH,
    "CORE_BUILD_EXAMPLES" : SWITCH
}

output_name = input("Name of the build script (omit extension): ") + ".py"
print()

vars = "{\n"
for (key, options) in zip(BUILD_VARS.keys(), BUILD_VARS.values()):
    prompt = f"Value for \"{key}\""

    for (index, option) in enumerate(options):
        if index == 0:
            prompt += " ("
        prompt += option
        if index == len(options) - 1:
            prompt += "): "
        else:
            prompt += ", "

    while True:
        selection = input(prompt)
        if options.__contains__(selection):
            break

    vars += f"\t\"{key}\" : \"{selection}\",\n"

vars += "}"

file = open(Path(__file__).parent / output_name, "w")
file.write(f"""
import configurator

configurator.configure_cmake({vars})
""")
file.close()

print(f"\nSuccessfully created build script \"{output_name}\"")