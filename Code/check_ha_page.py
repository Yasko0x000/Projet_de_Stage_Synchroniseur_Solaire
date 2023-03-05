import requests
import time

url = "http://homeassistant.local:8123"
config_url = url + "/config"

while True:
    try:
        response = requests.get(url)
        if response.status_code == 200:
            config_response = requests.get(config_url)
            if config_response.status_code == 200:
                print("La page est prête !")
                break
            else:
                print("La page est disponible, mais la configuration n'est pas encore prête...")
        else:
            print("La page n'est pas encore disponible, réessayez plus tard...")
    except requests.exceptions.RequestException as e:
        print("La page n'est pas encore disponible, réessayez plus tard...")
    time.sleep(10)