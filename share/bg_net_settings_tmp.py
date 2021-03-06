ipv4_net_addr_base = '10.7.0.1/24'
link_attr_default = ['2ms','5Mbps']
link_attr = {   (0, 1): ['0.002s', '5000000bps'],
    (0, 2): ['0.002s', '5000000bps'],
    (0, 6): ['0.002s', '5000000bps'],
    (2, 3): ['0.002s', '5000000bps'],
    (3, 4): ['0.002s', '5000000bps'],
    (4, 5): ['0.002s', '5000000bps'],
    (6, 7): ['0.002s', '5000000bps'],
    (8, 6): ['0.002s', '5000000bps'],
    (9, 6): ['0.002s', '5000000bps'],
    (10, 5): ['0.002s', '5000000bps'],
    (10, 11): ['0.002s', '5000000bps'],
    (12, 11): ['0.002s', '5000000bps'],
    (12, 13): ['0.002s', '5000000bps']}
link_to_ip_map = {   (0, 1): ('10.200.1.3/24', '10.200.1.1/24'),
    (0, 2): ('10.20.30.9/24', '10.20.30.1/24'),
    (0, 6): ('10.1.1.5/24', '10.1.1.1/24'),
    (2, 3): ('10.20.30.1/24', '10.20.30.2/24'),
    (3, 4): ('10.20.30.2/24', '10.20.30.3/24'),
    (4, 5): ('10.20.30.3/24', '10.20.30.4/24'),
    (6, 7): ('1.1.1.10/24', '1.1.1.1/24'),
    (8, 6): ('2.3.5.6/24', '2.3.5.10/24'),
    (9, 6): ('5.6.8.9/24', '5.6.8.10/24'),
    (10, 5): ('10.20.30.6/24', '10.20.30.4/24'),
    (10, 11): ('10.20.30.6/24', '10.20.30.7/24'),
    (12, 11): ('10.20.30.8/24', '10.20.30.7/24'),
    (12, 13): ('10.20.30.8/24', '10.20.30.5/24')}
