#!/bin/bash

get_info() {
    case "$1" in
        cpu)
            echo "CPU: $(grep 'model name' /proc/cpuinfo | head -n 1 | cut -d ':' -f2 | xargs)"
            ;;
        memory)
            mem_total=$(awk '/MemTotal/ {print $2}' /proc/meminfo)
            mem_free=$(awk '/MemFree/ {print $2}' /proc/meminfo)
            
            if [[ -z "$mem_total" || -z "$mem_free" ]]; then
                echo "Memory: Unable to retrieve memory information"
                return 1
            fi
            
            mem_used=$((mem_total - mem_free))
            mem_percent=$(( (mem_used * 100) / mem_total ))

            echo "Memory: $((mem_used / 1024)) / $((mem_total / 1024)) MiB ($mem_percent% used)"
            ;;
        load)
            load=$(uptime | awk -F 'load average:' '{print $2}' | xargs)
            echo "Load: $load"
            ;;
        uptime)
            uptime_seconds=$(cut -d. -f1 /proc/uptime)
            hours=$((uptime_seconds / 3600))
            minutes=$(((uptime_seconds % 3600) / 60))
            echo "Uptime: ${hours} hour(s), ${minutes} minute(s)"
            ;;
        kernel)
            echo "Kernel: $(uname -r)"
            ;;
        gpu)
            echo "GPU: $(lspci | grep -i 'vga' | cut -d ':' -f3 | xargs)"
            ;;
        user)
            echo "User: $USER"
            ;;
        shell)
            echo "Shell: $SHELL"
            ;;
        processes)
            echo "Processes: $(ps -e | wc -l)"
            ;;
        threads)
            echo "Threads: $(ps -eL | wc -l)"
            ;;
        ip)
            ip_info=$(ip -o -4 addr show | awk '{print $4}')
            echo "IP: $ip_info"
            ;;
        dns)
            dns_info=$(grep 'nameserver' /etc/resolv.conf | awk '{print $2}')
            echo "DNS: $dns_info"
            ;;
        internet)
            if timeout 1 ping -c 1 8.8.8.8 &> /dev/null; then
                echo "Internet: OK"
            else
                echo "Internet: Not Available"
            fi
            ;;
        *)
            echo "Invalid argument: $1" >&2
            return 1
            ;;
    esac
}

if [ $# -eq 0 ]; then
    get_info "cpu"
    get_info "memory"
    get_info "load"
    get_info "uptime"
    get_info "kernel"
    get_info "gpu"
    get_info "user"
    get_info "shell"
    get_info "processes"
    get_info "threads"
    get_info "ip"
    get_info "dns"
    get_info "internet"
else
    for arg in "$@"; do
        get_info "$(echo "$arg" | tr '[:upper:]' '[:lower:]')" || {
            exit 1
        }
    done
fi

exit 0
