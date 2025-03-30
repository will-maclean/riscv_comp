from elftools.elf.elffile import ELFFile

def get_entry_point(elf_file_path):
    with open(elf_file_path, 'rb') as f:
        elf = ELFFile(f)
        entry_point = elf.header['e_entry']
        print(elf.header)
        return entry_point

entry_point = get_entry_point("test.elf")
print(f"The entry point is at address 0x{entry_point:x}")