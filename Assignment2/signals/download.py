import requests

BASE_URL = "http://www.dirkwhoffmann.de/VL-ES/gps"

for i in range(1,29):
	url = f"{BASE_URL}/gps_sequence_{i}.txt"
	response = requests.get(url)
	if response.status_code == 200:
		with open(f"gps_sequence_{i}.txt", "wb") as f:
			f.write(response.content)
		print(f"Downloaded gps_sequence_{i}.txt")
	else:
		print(f"Failed to download gps_sequence_{i}.txt, status code: {response.status_code}")