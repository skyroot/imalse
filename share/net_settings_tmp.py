ipv4_net_addr_base = '10.7.0.1/24'
link_attr_default = ['2ms','5Mbps']
link_attr = {   (0, 1): ['0.01s', '10000000bps'],
    (0, 2): ['0.01s', '10000000bps'],
    (0, 3): ['0.01s', '10000000bps'],
    (0, 4): ['0.01s', '10000000bps'],
    (0, 5): ['0.01s', '10000000bps'],
    (0, 6): ['0.01s', '10000000bps'],
    (0, 7): ['0.01s', '10000000bps'],
    (8, 0): ['0.01s', '10000000bps'],
    (9, 0): ['0.01s', '10000000bps']}
link_to_ip_map = {   (0, 1): ('10.0.7.5/24', '10.0.7.4/24'),
    (0, 2): ('10.0.8.5/24', '10.0.8.4/24'),
    (0, 3): ('10.0.9.5/24', '10.0.9.4/24'),
    (0, 4): ('10.0.10.5/24', '10.0.10.4/24'),
    (0, 5): ('10.0.11.5/24', '10.0.11.4/24'),
    (0, 6): ('10.0.12.5/24', '10.0.12.4/24'),
    (0, 7): ('10.0.13.5/24', '10.0.13.4/24'),
    (8, 0): ('10.0.14.4/24', '10.0.14.5/24'),
    (9, 0): ('10.0.15.4/24', '10.0.15.5/24')}

pcap_nodes = [0, 1, 2]
pcap_links = [(0, 2)]
botmaster_id_set = []
client_id_set = []
server_id_set = []
server_addr = []