ipv4_net_addr_base = '10.7.0.1/24'
# link_to_interface_map
link_to_ip_map = {
        (0, 1):['10.0.1.1/24', '10.0.1.2/24'],
    }

link_attr_default = ['2ms','5Mbps']
link_attr = {
        (0, 1):['2ms','5Mbps'],
        }

# all links in pcap_links will export pcap data.
pcap_links = [(0, 1)]

# all nodes in pcap_nodes will export pcap data.
pcap_nodes = [0]

