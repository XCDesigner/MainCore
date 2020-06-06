import os

files = os.listdir(os.curdir)
cur_path = os.curdir
for f in files:
  print(f)
  if f.endswith(".c"):
    os.rename(cur_path + "\\" + f, cur_path + "\\" + f + "pp")