
amixer -c 1 cset numid=12,iface=MIXER,name='Line Capture Volume' 100%
amixer -c 1 sset 'PCM Capture Source' Line
