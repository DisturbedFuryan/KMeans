unset colorbox;
plot 'clustered_objects.txt' u 2:3:1 w points pt 7 ps 1 lc palette notitle, \
'centers.txt' u 2:3:1 w points pt 3 ps 2 lc palette notitle;
