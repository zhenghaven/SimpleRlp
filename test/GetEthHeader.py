from GethDBReader import GethDB

HEADER_NUM = 0

def print_b(h):
	s = ["{:#04X}U".format(x) for x in h]
	i = 1
	r = ''
	for x in s:
			r += (x + ', ')
			r += '\n' if (i % 10 == 0) else ''
			i += 1
	print(r)

db = GethDB.GethDB('', '/home/public/geth-ancient/')

h = db.freezerdb.tables['headers'].Retrieve(HEADER_NUM)
print_b(h)
