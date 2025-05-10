#include "io.h"

int cprint(FILE* stream, format_mode mode, const char* format, ...)
{
  va_list args;
  va_start(args, format);

  const char* cursor = format;
  int written = 0;

  while(*cursor)
  {
    if(*cursor == '%' && *(cursor+1) == 'v')
    { // Custom '%v' format specifier
      literal* value = va_arg(args, literal*);
      char buffer[STR_MAX_LENGTH];
      val2str(buffer, sizeof(buffer), mode, value);
      fprintf(stream, "%s", buffer);
      cursor+=2;
    }
    else if(*cursor == '%')
    { // Other format specifiers
      cursor++;
      if(*cursor)
      {
        char specifier[3] = {'%', *cursor, '\0'};
        if(*cursor == '%')
        { // %%
          fputc('%', stream);
          written++;
        }
        else
        {
          switch(*cursor)
          {
            case 'd': written += fprintf(stream, specifier, va_arg(args, int)); break;
            case 'f': written += fprintf(stream, specifier, va_arg(args, double)); break;
            case 'c': written += fprintf(stream, specifier, (char)va_arg(args, int)); break;
            case 's': written += fprintf(stream, specifier, va_arg(args, char*)); break;
            default: 
            { // Unknown specifier, print it
              fputc('%', stream);
              fputc(*cursor, stream);
              written+=2;
              break;
            }
          }
        }
        cursor++;
      }
    } 
    else
    { // Print other characters
      fputc(*cursor, stream);
      written++;
      cursor++;
    }
  }

  va_end(args);
  return written;
}


