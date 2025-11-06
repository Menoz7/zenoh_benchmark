sudo sysctl -w net.core.rmem_max=134217728
sudo sysctl -w net.core.wmem_max=134217728
sudo sysctl -w net.core.rmem_default=134217728
sudo sysctl -w net.core.wmem_default=134217728
sudo sysctl -w net.ipv4.udp_mem="102400 873800 16777216"
