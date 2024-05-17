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

## Install and Use

- Install [osmanip](https://github.com/JustWhit3/osmanip) as written [here](https://github.com/JustWhit3/osmanip?tab=readme-ov-file#install)
- Download our latest release
- In the downloaded folder:
  ```
  $ mkdir build
  $ cd build
  $ cmake ..
  ```
- Compile project:
  ```
  $ make
  ```
- And run it:
  ```
  $ ./TetrisBot
  ```
  If you want to change the number of threads (by default all threads are used), you should run the project like this:
  ```
  $ OMP_NUM_THREADS=x ./TetrisBot
  ```
  where `x` is preferred number of threads.
  
  **Note**: If you want to change the time between frames, you have to go in `settings.h`, change the value of `FrameTime` to whatever you want, and then compile project again. In the same way, you can change the number of pieces known to the bot (value of `KnownPiecesCount`), but keep in mind that the calculation time will grow exponentially.
