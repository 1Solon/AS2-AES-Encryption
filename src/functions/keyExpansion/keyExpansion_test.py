import pytest, ctypes, subprocess, os
from ctypes import c_uint8 as uint8_t

S_BOX = (uint8_t * 256)(*[
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
    ])

R_CON = (uint8_t * 11)(*([0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C]))

keyLen = 16
totalKeyLen = 176

# Define the test cases, these were taken from the AES standard
test_cases = [
    ('E8E9EAEBEDEEEFF0F2F3F4F5F7F8F9FA', 'E8E9EAEBEDEEEFF0F2F3F4F5F7F8F9FAA870C783459E2873B76DDC864095257C804FD78AC5D1FFF972BC237F322906032120ACA9E4F15350964D702FA464762C6A18DDE08EE98EB018A4FE9FBCC088B3C0DCB0854E353E355691C0AAEA514819318E64027FBB5A37292A9A9DC37BD284503B3B2C2F80611B06AAFB86C5D12902EE9E4C8AC11E2D91C7B4D6170265FF15B88815FD7996386CBE22EE7BBC47116E2E0A8A98579CB2F4E9BE5C8F55F94DE1'),
    ('A1A2A3A4A5A6A7A8A9AAABACADAEAFB0', 'A1A2A3A4A5A6A7A8A9AAABACADAEAFB044DB4431E17DE39948D74835E579E785F04FD3E81132307159E57844BC9C9FC12A94AB8D3BA69BFC6243E3B8DEDF7C79BC841D908722866CE56165D43BBE19AD0250887285720E1E60136BCA5BAD7267B7100D4B326203555271689F09DC1AF871B24C4A43D04F1F11A12780187D3D780E95F0E74D45BFF85CE498784499A500FB9393FCB6D62C04EA32B47CAEAB117CAF11831819C7AF1CF3F51B605D5E0A1C'),
    ('B1B2B3B4B5B6B7B8B9BABBBDBEBFB0B1', 'B1B2B3B4B5B6B7B8B9BABBBDBEBFB0B1B8557B1A0DE3CCA2B459771F0AE6C7AE34939F7D397053DF8D2924C087CFE36EBA82006A83F253B50EDB77758914941B48A0AFCDCB52FC78C5898B0D4C9D1F160660E8E4CD32149C08BB9F9144268087D1ADFFFF1C9FEB63142474F25002F475E61262ACFA8D89CFEEA9FD3DBEAB094804133002FE9EB9CD103744F0AE9C4DB8C1F05CE63F6EE52B2F59A1DB81C5EC63513EA7EA6E5042C14109E31AC0CC0F79'),
    ('C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0', 'C1C2C3C4C5C6C7C8C9CACBCCCDCECFD04B48B3798E8E74B14744BF7D8A8A70AD37192607B99752B6FED3EDCB74599D66F847159541D04723BF03AAE8CB5A378E4EDD0C8A0F0D4BA9B00EE1417B54D6CF7E2B86AB7126CD02C1282C43BA7CFA8C4E06E25F3F202F5DFE08031E4474F9929C9FAD44A3BF82195DB7810719C3789532238790919C0589CC2B848ED5E8FC1BB2932893230F2D1AEF24A9943ACC558FCF6F5B13EC6076090344DF9D39888A12')
    ]

lib = ctypes.CDLL("build/libmyProgram_lib.so")

@pytest.mark.parametrize("inputKey, expected", test_cases)
def test_keyExpansion(inputKey, expected):
    expandedKeys = (uint8_t * 176)()

    # Call the function from the shared library and get the result back as a string of hex values 
    lib.KeyExpansion(bytes.fromhex(inputKey), expandedKeys, S_BOX, R_CON, keyLen, totalKeyLen)
    testKey = (''.join([hex(key)[2:].zfill(2) for key in expandedKeys])).upper()

    assert testKey == expected, f"For inputKey: {inputKey}, expected: {expected}, but got: {testKey}"