# TetrisBot

Bot that plays tetris.

- OMP for paralleling
- CMake as build system
- [osmanip](https://github.com/JustWhit3/osmanip) as external library

[UML Diagram](https://app.diagrams.net/?lightbox=1&edit=_blank#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1J4p-DZc6yyeZNowf1WxNtWOcEeMHKPMV%26export%3Ddownload#%7B%22pageId%22%3A%227fJ11CMw67HMKrH62q-I%22%7D)

## Performance Test

1 thread | 2 threads | 4 threads
:-------------------------:|:-------------------------:|:-------------------------:
![1thr_no](https://github.com/k7ps/TetrisBot/assets/95523848/b1bb57db-9d9c-4088-b532-94a5017ca783) | ![2thr_no](https://github.com/k7ps/TetrisBot/assets/95523848/204311c5-e3a6-4291-9f18-6aa1b0ae9a30) | ![4thr_no](https://github.com/k7ps/TetrisBot/assets/95523848/22c78a2c-173a-491a-ac63-0bd26bbabc13)
~120ms | ~66ms | ~53ms
| — | **1.8** times faster | **2.2** times faster
