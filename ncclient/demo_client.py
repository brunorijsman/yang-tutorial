from ncclient import manager

with manager.connect(host="127.0.0.1", 
                     port=830, 
                     username="parallels", 
                     password="Virtu33l?",
                     hostkey_verify=False) as m:
#                     device_params={'name':'alu'}) as m:
    c = m.get_config(source='running').data_xml
    with open("out.xml", 'w') as f:
        f.write(c)
