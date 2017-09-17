#!/usr/bin/env python3
import sys
import re
key_re = re.compile(r'[a-zA-Z]*([0-9]*)')
def handle_update_match(match, f):
    key = match.group(1)
    subkey = match.group(2)
    value = match.group(3)
    kmatch = key_re.match(key)
    if not kmatch:
        print("DID NOT MATCH KEY???", file=sys.stderr)
        print(key)
        sys.exit(1)
    userid = int(kmatch.group(1))
    partition = userid % hosts
    print('%d UPDATE %s-%s %s'%(partition, key, subkey, value), file=f)
def handle_get_match(match, f):
    key = match.group(1)
    subkey = match.group(2)
    kmatch = key_re.match(key)
    if not kmatch:
        print("DID NOT MATCH KEY???", file=sys.stderr)
        print(key)
        sys.exit(1)
    userid = int(kmatch.group(1))
    partition = userid % hosts
    print('%d GET %s-%s'%(partition, key, subkey), file=f)

def main(args):
    if len(args) != 4:
        print("Usage: %s <input> <output_pfx> <nhosts>"%(args[0]), file=sys.stderr)
        print("\t input is generated using mockdb")
        sys.exit(1)
    update_re = re.compile(r'UPDATE\s*(\S+)\s*(\S+)\s*(\S+)\s*')
    get_re = re.compile(r'GET\s*(\S*)\s*(\S+)\s*')
    global hosts
    hosts = int(args[3])
    pfx = args[2]
    with open(args[1]) as infile:
        load_file = open("%s.load"%pfx, 'w')
        for l in infile:
            if l.startswith('=%=%=%= LOADED =%=%=%='):
                break
            match = update_re.match(l)
            if not match:
                print("DID NOT MATCH UPDATE???", file=sys.stderr)
                print(l)
                sys.exit(1)
            handle_update_match(match, load_file)
        load_file.close()
        access_file = open("%s.access"%pfx, 'w')
        for l in infile:
            match = update_re.match(l)
            if match:
                handle_update_match(match, access_file)
            else:
                match = get_re.match(l)
                if not match:
                    print("Neither get nor update", file=sys.stderr)
                    print(l)
                    sys.exit(1)
                handle_get_match(match, access_file)

if __name__ == "__main__":
    main(sys.argv)
