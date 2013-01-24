#include<stdio.h>
#include<string.h>
#include<stdint.h>

#define PRESET_SIZE 76

uint8_t data_to_sysex(uint8_t *data, uint8_t *sysex, uint8_t len) {
  uint8_t retlen = 0;
  uint8_t cnt;
  uint8_t cnt7 = 0;

  sysex[0] = 0;
  for (cnt = 0; cnt < len; cnt++) {
    uint8_t c = data[cnt] & 0x7F;
    uint8_t msb = data[cnt] >> 7;
    sysex[0] |= msb << cnt7;
    sysex[1 + cnt7] = c;

    if (cnt7++ == 6) {
      sysex += 8;
      retlen += 8;
      sysex[0] = 0;
      cnt7 = 0;
    }
  }
  return retlen + cnt7 + (cnt7 != 0 ? 1 : 0);
}

uint8_t sysex_to_data(uint8_t *sysex, uint8_t *data, uint8_t len) {
  uint8_t cnt;
  uint8_t cnt2 = 0;
  uint8_t bits = 0;
  for (cnt = 0; cnt < len; cnt++) {
    if ((cnt % 8) == 0) {
      bits = sysex[cnt];
    } else {
      data[cnt2++] = sysex[cnt] | ((bits & 1) << 7);
      bits >>= 1;
    }
  }
  return cnt2;
}


int main(void)
{
    FILE* read_fd = NULL;
    FILE* write_fd = NULL;
    uint8_t read_buff[76];
    uint8_t write_buff[128];
    memset(read_buff,0,sizeof(read_buff));

    read_fd = fopen("BASMAN.mwp","rw+");
    write_fd = fopen("BASMAN.mwp2","wb");

    if((NULL == read_fd)||(NULL == write_fd))
    {
        printf("\n fopen() Error!!!\n");
        return 1;
    }


    if(PRESET_SIZE != fread(read_buff,1, PRESET_SIZE,read_fd))
    {
        printf("\n fread() failed\n");
        return 1;
    }

    int a = sysex_to_data(read_buff, write_buff, sizeof(read_buff));

    printf("sysex_to_data: %d", a);

    if(PRESET_SIZE != fwrite(write_buff,sizeof(write_buff),1,write_fd))
    {
        printf("\n fwrite() failed\n");
        return 1;
    }

    printf("\n fwrite() successful, data written to text file\n");

    fclose(read_fd);
    fclose(write_fd);
    return 0;
}
