# **PROGRAM GAME MARIO BROS**
#### Mata Kuliah Proyek 2: Pemanfaatan Aplikasi berbasis Library

<p align="center">
  <img src="https://raw.githubusercontent.com/Zsweetieszt/Proyek2/master/assets/name.png" alt="Logo" />
</p>

## 🕹️ TENTANG GAME
    
`Game ini adalah 2D platformer bergaya Mario Bros yang dibuat menggunakan bahasa C dan library graphics.h. 
Pemain mengontrol karakter utama yang dapat berjalan, melompat, dan menghindari atau mengalahkan musuh sambil mengumpulkan koin dan bintang di sepanjang level. 
Tujuan utama pemain adalah mencapai bendera akhir level atau portal untuk melanjutkan ke level berikutnya.`

## 🚀 TEKNOLOGI YANG DIGUNAKAN

- 🔧 `Bahasa: C`
- 🧱 `Library: graphics.h`
- 🔊 `Audio: PlaySound`
- 📂 `File I/O: Untuk leaderboard dan skor`

## 🎮 FITUR UTAMA

  1. Animasi & Kontrol Pemain
     * `Pemain dapat berjalan, melompat, dan berdiri diam, dengan animasi sprite berbasis pixel art (matriks warna).`
  2. Deteksi Tabrakan (Collision Detection)
     `Pemain dapat berinteraksi dengan berbagai objek di dunia permainan, seperti:`
      - `Koin (coin) dan bintang (star) → dikumpulkan untuk poin dan kekuatan khusus.`
      - `Paku (spike) dan monster → menyebabkan game over jika disentuh tanpa perlindungan.`
      - `Blok/platform → pijakan tempat pemain berdiri atau meloncat.`
      - `Bendera (flag) dan portal → menandai akhir level atau transisi ke level berikutnya.`
  3. Musuh (Monster)
     * `Monster bergerak bolak-balik secara otomatis dalam rentang tertentu yang dapat dikalahkan dengan mendapatkan efek "star power"`
  4. Level & Peta (Map)
     * `Setiap level diwakili sebagai array 2D tile, yang terdiri peta memuat posisi objek seperti monster, koin, paku, flag, dan lainnya.`
  5. UI & Menu Interaktif
     - `Menu utama dengan opsi: Start, Guide, Leaderboard, dan Exit.`
     - `Input nama pemain saat memulai permainan.`
     - `Tampilan leaderboard yang terintegrasi ke dalam menu.`
  6. Leaderboard

      - `Menyimpan nama dan skor pemain.`
      - `Memuat dan menyimpan data ke file leaderboard.txt.`
      - `Menampilkan 10 skor tertinggi secara grafis di menu.`
  8. Audio & Efek Suara   
     - `Musik latar (background music / BGM) selama permainan.`
     - `Efek suara saat menang (win.wav) atau kalah (gameover.wav).`
       
## 📁 STRUKTUR FILE

  -  `Collision`
  -  `Game`
  -  `Leaderboard`
  -  `Main menu`
  -  `Map`
  -  `Player`

## 🧩 TO DO

    [✅]  Membuat tampilan game menjadi full screen
    [✅]  Menambahkan fitur leaderboard
    [✅]  Memperindah tampilan main menu
    [✅]  Menambahkan backsound


# 📦 Instalasi & Menjalankan Game
<details> <summary><strong>Klik untuk melihat panduan lengkap 📖</strong></summary>
  
## 🛠️ Persyaratan

- Compiler: C (MinGW atau Code::Blocks)
- Library: `graphics.h` + `libbgi.a`
- OS: Linux / Windows / macOS

1. **Clone repositori:**

       git clone https://github.com/username/repo.git
       cd repo


 2. Pasang `graphics.h`
  - Unduh library dari [winbgim.codecutter.org](http://winbgim.codecutter.org/) dan ikuti petunjuk instalasinya.
  - Simpan:
    <br>`graphics.h` → `MinGW/include`</br>
    <br>`libbgi.a` → `MinGW/lib`</br>
 3. Kompilasi

        gcc main.c collision.c game.c map.c main_menu.c leaderboard.c player.c -o game.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm
 4. Jalankan game

        ./game.exe
<p align="center">
  <img src="https://raw.githubusercontent.com/Zsweetieszt/Proyek2/master/assets/logo.png" alt="Logo" />
</p>
