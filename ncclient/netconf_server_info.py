import psutil
import os


def address():
    address = os.getenv('NETCONF_SERVER_ADDRESS')
    if address is None:
        return '127.0.0.1'
    return address


def username():
    username = os.getenv('NETCONF_SERVER_USERNAME')
    if username is None:
        return psutil.Process().username()
    return username


def password():
    return os.getenv('NETCONF_SERVER_PASSWORD')
