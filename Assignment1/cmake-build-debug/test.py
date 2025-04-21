import subprocess

with open("result.txt", "w") as f:
	for i in range(1,29):
		testFile = f"../signals/gps_sequence_{i}.txt"
		print(f"Testing {testFile}")
		f.write(f"Testing {testFile}\n")
		result = subprocess.check_output(["Assignment1.exe", testFile])
		txt = result.decode("utf-8")
		lines = [line for line in txt.split("\r\n") if line.strip()]
		writeText = "\n".join(lines)
		print(writeText)
		print("--------------------------------------------------")
		f.write(writeText)
		f.write("\n")
		f.write("--------------------------------------------------\n")

