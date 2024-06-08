#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 5000

char C[MAX_TEXT_LENGTH],M[MAX_TEXT_LENGTH],Key[50];

const float english_freq[ALPHABET_SIZE] =
{
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
char ciphertext[] = "hzsrnqc klyy wqc flo mflwf ol zqdn nsoznj wskn lj xzsrbjnf, wzsxz gqv zqhhnf ol ozn glco zlfnco hnlhrn; nsoznj jnrqosdnc lj fnqj kjsnfbc, wzsxz sc xnjoqsfrv gljn efeceqr. zn rsdnb qrlfn sf zsc zlecn sf cqdsrrn jlw, wzsoznj flfn hnfnojqonb. q csfyrn blgncosx cekksxnb ol cnjdn zsg. zn pjnqmkqconb qfb bsfnb qo ozn xrep, qo zlejc gqozngqosxqrrv ksanb, sf ozn cqgn jllg, qo ozn cqgn oqprn, fndnj oqmsfy zsc gnqrc wsoz loznj gngpnjc, gexz rncc pjsfysfy q yenco wsoz zsg; qfb wnfo zlgn qo naqxorv gsbfsyzo, lfrv ol jnosjn qo lfxn ol pnb. zn fndnj ecnb ozn xlcv xzqgpnjc wzsxz ozn jnkljg hjldsbnc klj soc kqdlejnb gngpnjc. zn hqccnb onf zlejc leo lk ozn ownfov-klej sf cqdsrrn jlw, nsoznj sf crnnhsfy lj gqmsfy zsc olsrno"

                    ;
void calculate_frequency(const char *text, float *freq)
{
    int count[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            count[tolower(text[i]) - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        freq[i] = ((float)count[i] / total) * 100;
    }
}

char find_closest_freq(float freq, const float *english_freq, int *used)
{
    float min_diff = 100.0;
    char best_match = 'a';

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (!used[i])
        {
            float diff = (english_freq[i] > freq) ? (english_freq[i] - freq) : (freq - english_freq[i]);
            if (diff < min_diff)
            {
                min_diff = diff;
                best_match = 'a' + i;
            }
        }
    }

    return best_match;
}

void generate_decryption_table(const float *text_freq, char *decryption_table)
{
    int used[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        char match = find_closest_freq(text_freq[i], english_freq, used);
        decryption_table[i] = match;
        used[match - 'a'] = 1;
    }
}

void decrypt_text(const char *ciphertext, const char *decryption_table, char *plaintext)
{
    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char decrypted_char = decryption_table[tolower(ciphertext[i]) - 'a'];
            plaintext[i] = isupper(ciphertext[i]) ? toupper(decrypted_char) : decrypted_char;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void manual_adjustment(char *decryption_table, const char *ciphertext)
{

    char from, to;
    char current_plaintext[MAX_TEXT_LENGTH];

    do
    {
        decrypt_text(ciphertext, decryption_table, current_plaintext);
        printf("初始密文：\n%s\n", ciphertext);
        printf("当前解密结果：\n%s\n", current_plaintext);




        printf("输入需要调整的密文字符:(输入0结束) ");
        scanf(" %c", &from);
        if(from=='0') break;
        from = tolower(from);
        printf("输入对应的明文字符: ");
        scanf(" %c", &to);
        to = tolower(to);

        decryption_table[from - 'a'] = to;

    }
    while (1);
}
void cm(void)
{
    int i,j;
    printf("请输入明文（小写）\n");
    scanf("%s",C);
    printf("请依次输入从a到z各个字母对应的代换密文\n");
        scanf("%s",Key);
    for(i=0; i<strlen(C)+1; i++)
    {
        j=C[i]-'a';
        if(j>=0&&j<27)
            printf("%c",Key[j]);
        else
            printf("%c",C[i]);
    }
}

void mc(void)
{
    int i,j;
    printf("请输入密文（小写）\n");
    scanf("%s",M);
    printf("请依次输入从a到z各个字母对应的代换明文\n");
        scanf("%s",Key);
    for(i=0; i<strlen(M)+1; i++)
    {
        j=M[i]-'a';
        if(j>=0&&j<27)
            printf("%c",Key[j]);
        else
            printf("%c",M[i]);
    }

}
int main()
{
    int f;
    char plaintext[MAX_TEXT_LENGTH];
    float text_freq[ALPHABET_SIZE] = {0};
    char decryption_table[ALPHABET_SIZE] = {0};
    printf("1）加密\n2）解密\n3）破译题目密文\n");
    scanf("%d",&f);
    switch(f)
    {
    case 1:
        cm();//由C到M，即加密
        break;
    case 2:
        mc();//由M到C,即解密
        break;
    case 3:


        calculate_frequency(ciphertext, text_freq);
        generate_decryption_table(text_freq, decryption_table);


        // 手动调整破译表
        manual_adjustment(decryption_table, ciphertext);

        decrypt_text(ciphertext, decryption_table, plaintext);

        printf("最终解密结果：\n%s\n", plaintext);
        break;//解密结果应为：phileas fogg was not known to have either wife or children, which may happen to the most honest people; either relatives or near friends, which is certainly more unusual. he lived alone in his house in saville row, whither none penetrated. a single domestic sufficed to serve him. he breakfasted and dined at the club, at hours mathematically fixed, in the same room, at the same table, never taking his meals with other members, much less bringing a guest with him; and went home at exactly midnight, only to retire at once to bed. he never used the cosy chambers which the reform provides for its favoured members. he passed ten hours out of the twenty-four in saville row, either in sleeping or making his toilet

    }

    return 0;
}

