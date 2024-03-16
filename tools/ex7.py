SIZE = 23

res = ''
stack = []
for x in range(SIZE + 1):
	res += '\t' * len(stack) + 'POWER(\n'
	stack.append(x)

while len(stack) > 0:
	indent = len(stack)
	elem = stack.pop()
	res += '\t' * indent + ('* ' if elem != SIZE else '')+ 'CASE WHEN RSHIFT(p.privD, ' + str(elem) + ') % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,\n'
	res += '\t' * indent + '2\n'
	res += '\t' * (indent-1) + ') % p.pubN\n'

with open('res.txt', 'w') as f:
	f.write(res)
	f.close()
