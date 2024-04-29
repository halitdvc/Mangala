#include <stdio.h>
#define TABLO_BOYUTU 14

int oyun_tablosu[TABLO_BOYUTU];
int su_anki_oyuncu;

// Oyun tahtasını başlat
void oyunTahtasiniBaslat() {
    for(int i=0; i<TABLO_BOYUTU; i++) {
        // taşları oyuncuların çukurlarına koy (son ikisi her oyuncunun evi)
        oyun_tablosu[i] = (i != 6 && i != 13) ? 4 : 0;
    }
}

// Tahtayı göster
void oyunTahtasiniGoster() {
    printf("Mevcut Tahta:\n");
    for (int i=0; i<TABLO_BOYUTU; i++) {
        printf("%d: %d ", i, oyun_tablosu[i]);
    }
    printf("\n");
}

// Bir oyuncunun hamlesini yap
int hamleyiYap(int cuku) {
    int taslar = oyun_tablosu[cuku];
    oyun_tablosu[cuku] = 0;
    while (taslar > 0) {
        cuku = (cuku + 1) % TABLO_BOYUTU;

        // oyun sırasında kendi evine taş bırak ama karşı tarafın evine bırakma
        if ((su_anki_oyuncu == 0 && cuku != 13) || (su_anki_oyuncu == 1 && cuku != 6)) {
            oyun_tablosu[cuku]++;
            taslar--;
        }
    }

    // sıra olan oyuncunun evinde bitiş kontrolü
    if ((su_anki_oyuncu == 0 && cuku == 6) || (su_anki_oyuncu == 1 && cuku == 13)) {
        return 1;
    } else {
        su_anki_oyuncu = 1 - su_anki_oyuncu; // sırayı değiştir
        return 0;
    }
}

// Oyunun bitip bitmediğini kontrol et
int oyunBittiMi()
{
    for(int i = 0; i<TABLO_BOYUTU; i++) {
        // çukurlarda taş var mı kontrol et
        if ((i < 6 || (i > 6 && i < 13)) && oyun_tablosu[i] != 0) {
            return 0; // taşları olan çukur varsa, oyun devam eder
        }
    }
    return 1; // tüm çukurlar boşsa oyun biter
}

int main()
{
    oyunTahtasiniBaslat();
    while (!oyunBittiMi()) {
        oyunTahtasiniGoster();
        int hamle;
        printf("\nOyuncu %d'nin hamlesi: ", su_anki_oyuncu+1);
        scanf("%d", &hamle);
        hamleyiYap(hamle);
    }
    printf("\nOyun Bitti!");
    return 0;
}