ipv4_net_addr_base = '10.7.0.1/24'
link_attr_default = ['2ms','5Mbps']
link_to_ip_map = {
	(2, 0):['10.0.0.20/24', '10.0.0.1/24'],
	(3, 0):['10.0.1.20/24', '10.0.1.1/24'],
	(0, 1):['10.0.2.1/24', '10.0.2.2/24'],
	(4, 1):['10.0.3.20/24', '10.0.3.1/24'],
	(5, 1):['10.0.4.20/24', '10.0.4.1/24'],
}
link_attr = {
	(3, 0):['80 ms', '64.00 Kbps'],
}
pcap_nodes = [ 0, 1, 2, 3, 4, 5 ]
pcap_links = [ (2,0) ]
botmaster_id_set = [ 3 ]
client_id_set = [ 4, 5 ]
server_id_set = [ 2 ]
server_addr = [ "10.0.1.20/24" ]
