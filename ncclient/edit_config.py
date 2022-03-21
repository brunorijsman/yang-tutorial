from ncclient import manager
import netconf_server_info


with manager.connect(host=netconf_server_info.address(),
                     port=830,
                     username=netconf_server_info.username(),
                     password=netconf_server_info.password(),
                     hostkey_verify=False,
                     device_params={'name': 'alu'}) as mgr:

    cfg_interface = """
        <config>
            <interfaces xmlns="http://remoteautonomy.com/yang-schemas/interfaces">
                <interface>
                    <name>eth1</name>
                    <ipv4-address>2.2.2.2</ipv4-address>
                </interface>
            </interfaces>        
        </config>
    """
    reply = mgr.edit_config(config=cfg_interface)
    assert reply.xpath("/rpc-reply/ok") != []
    reply = mgr.commit()
    assert reply.xpath("/rpc-reply/ok") != []
