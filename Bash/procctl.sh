#!/bin/bash

list_top_cpu() {
    echo "Top 5 processes by CPU usage:"
    ps aux --sort=-%cpu | head -n 6
}

list_top_memory() {
    echo "Top 5 processes by memory usage:"
    ps aux --sort=-%mem | head -n 6
}

show_process_tree() {
    echo "Process tree:"
    pstree
}

show_process_name_by_pid() {
    read -p "Enter PID: " pid
    if [[ -e /proc/$pid ]]; then
        echo "Process name for PID $pid: $(cat /proc/$pid/comm)"
    else
        echo "Invalid PID"
    fi
}

show_pid_by_name() {
    read -p "Enter process name: " pname
    pids=$(pgrep -f "$pname")
    if [[ -z "$pids" ]]; then
        echo "No processes found for name: $pname"
    else
        echo "PID(s) for process $pname: $pids"
    fi
}

kill_process_by_pid() {
    read -p "Enter PID to kill: " pid
    if kill $pid 2>/dev/null; then
        echo "Process $pid killed successfully."
    else
        echo "Failed to kill process $pid."
    fi
}

kill_process_by_name() {
    read -p "Enter process name to kill: " pname
    if pkill -f "$pname"; then
        echo "Processes named $pname killed successfully."
    else
        echo "Failed to kill processes named $pname."
    fi
}

while true; do
    echo "Process Control:"
    echo "1) List top 5 processes by CPU usage"
    echo "2) List top 5 processes by memory usage"
    echo "3) Show process tree"
    echo "4) Show process name by PID"
    echo "5) Show process PID(s) by name"
    echo "6) Kill process by PID"
    echo "7) Kill process by name"
    echo "q) Exit"
    
    read -p "Choice: " choice

    case "$choice" in
        1) list_top_cpu ;;
        2) list_top_memory ;;
        3) show_process_tree ;;
        4) show_process_name_by_pid ;;
        5) show_pid_by_name ;;
        6) kill_process_by_pid ;;
        7) kill_process_by_name ;;
        q) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice, please try again." ;;
    esac
done
