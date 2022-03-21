from ncclient import manager
from bs4 import BeautifulSoup
import netconf_server_info


with manager.connect(host=netconf_server_info.address(),
                     port=830,
                     username=netconf_server_info.username(),
                     password=netconf_server_info.password(),
                     hostkey_verify=False,
                     device_params={'name': 'alu'}) as mgr:
    print("Client capabilities:")
    for capability in mgr.client_capabilities:
        print(f"  {capability}")
    print("Server capabilities:")
    for capability in mgr.server_capabilities:
        print(f"  {capability}")
