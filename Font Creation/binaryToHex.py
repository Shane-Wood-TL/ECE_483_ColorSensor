def binary_to_hex(binary_array):
    hex_list = []
    for binary in binary_array:
        hex_value = f'0x{int(binary, 2):04X}, //{binary}'
        hex_list.append(hex_value) 
    return hex_list

binary_input = """
{B00000000000000000000,
B00001110000000000000,
B00011111000000000000,
B00110001100000000000,
B00110001100000000000,
B01100000110000000000,
B01100000110000000001,
B11000000011000000011,
B10000000001100000110,
B00000000000100000110,
B00000000000110001100,
B00000000000011111000,
B00000000000001110000,
B00000000000000000000}
"""


binary_representation = [line.strip() for line in binary_input.strip('{}\n').split(',')]


cleaned_binary = [b[1:] for b in binary_representation]

hex_values = binary_to_hex(cleaned_binary)

print("uint16_t name[] = {")
for hex_value in hex_values:
    print(hex_value)
print("};")
