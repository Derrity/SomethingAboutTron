#!/bin/bash
apt update
apt install cmake make libcurl4-openssl-dev libssl-dev libboost-all-dev gcc g++ clang wget unzip -y

mkdir v2ray
cd v2ray
wget https://github.com/v2fly/v2ray-core/releases/download/v5.13.0/v2ray-linux-64.zip
unzip v2ray-linux-64.zip
chmod +x v2ray

cat > config.json << EOF
{
    "inbounds": [
        {
            "port": 10809,
            "listen": "127.0.0.1",
            "protocol": "http",
            "settings": {
                "udp": true
            }
        }
    ],
    "outbounds": [
        {
            "protocol": "vless",
            "settings": {
                "vnext": [
                    {
                        "address": "worker-quiet-hat-16d6.kayifaint28.workers.dev",
                        "port": 80,
                        "users": [
                            {
                                "id": "f3d0e48d-3f27-42b0-8975-b2806fd31bb7",
                                "encryption": "none"
                            }
                        ]
                    }
                ]
            },
            "streamSettings": {
                "network": "ws",
                "security": "none",
                "wsSettings": {
                    "path": "/?ed=2048",
                    "headers": {
                        "Host": "worker-quiet-hat-16d6.kayifaint28.workers.dev"
                    }
                }
            }
        }
    ]
}
EOF

nohup ./v2ray run -config config.json > v2ray.log 2>&1 &

cd ..

mkdir -p build
cd build 
cmake ..
make -j
chmod +x checkbitbalance
mv checkbitbalance ..

cd ..
echo -e "\033[0;32m Done! \033[0m Run ./server to start the server"
