#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
using namespace std;
// pair<int, int> getsize(u_char *header_bytes);
int loadBmp(const char fn[], int *w, int *h, int *bit) {
    FILE *fp;               // ファイルポインタの宣言
    unsigned char hdr[54];  // ヘッダ格納用の配列
    int i;                  // ループ用変数

    // bmpファイルをバイナリモードで読み取り
    fp = fopen(fn, "rb");

    // 画像ファイルが見つからない場合のエラー処理
    if (fp == NULL) {
        printf("Not found : %s \n", fn);
        exit(-1);
    }

    // ヘッダ情報の読み込み
    for (i = 0; i < 54; i++) hdr[i] = fgetc(fp);

    // 画像がビットマップで無い場合のエラー処理
    if (!(hdr[0] == 'B' && hdr[1] == 'M')) {
        printf("%Not BMP file : &s \n", fn);
        exit(-1);
    }

    // ヘッダ情報から画像の幅、高さ、ビットの深さを抽出
    *w = hdr[18] + hdr[19] * 256;
    *h = hdr[22] + hdr[23] * 256;
    *bit = hdr[28];

    fclose(fp);  // ファイルを閉じる

    return 0;
}
vector<vector<bool>> readBmp(const char filename[], int width, int height, int depth) {
    FILE *fp;
    vector<vector<bool>> data;
    data.resize(height);
    for (auto i : data) i.resize(width);
    fp = fopen(filename, "rb");
    vector<u_char> bmpdata;
    while (fgetc(fp) != NULL) bmpdata.push_back(fgetc(fp));
}
int main(int argc, char const *argv[]) {
    int w, h, depth;
    loadBmp(argv[1], &w, &h, &depth);

    // 読み取り結果表示
    printf("画像の幅=%d[px]：\n", w);
    printf("画像の高さ=%d[px]\n", h);
    printf("ビット数=%d[bit]\n", depth);
    printf("チャンネル数=%d[ch]", depth / 8);
    readBmp(argv[1], w, h, depth);
    return 0;
}
