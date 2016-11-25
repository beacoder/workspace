#!/usr/bin/env python

import re
import argparse
import json
import sys

def usage():
  sample ="""Filter only application/framework json:
e.g: ./jsonFilter.py -f /repo/ehumche/epg__0/build/Linux_x86_64/compile_commands.json -t /git/ehumche/epg__0/application,/git/ehumche/epg__0/framework -o out.json
  """
  print sample
  return

def doMatch(json_obj, filters):
  fileStr = json_obj.get('file')
  if fileStr:
    for f in filters:
       if re.search(f, fileStr):
         return True
  return False

def doFilter(input_json, filters, output_json):

  # Transform json input to python objects
  with open(input_json) as data_file:
    input_dict = json.load(data_file)

  # Filter python objects with list comprehensions
  output_dict = [x for x in input_dict if doMatch(x, filters)]

  # Transform python object back into json
  with open(output_json, 'w') as outfile:
    json.dump(output_dict, outfile, indent=2)

  # Show json
  # print output_json

  return

def createParser():
  p = argparse.ArgumentParser()
  p.add_argument("-f")
  p.add_argument("-t")
  p.add_argument("-o")
  args = p.parse_args()
  return args

def main():
  args = createParser()
  if args.f and args.o and args.t:
    doFilter(args.f, args.t.split(","), args.o)
  else:
    usage()
  sys.exit(0)

if __name__ == "__main__":
    main()
