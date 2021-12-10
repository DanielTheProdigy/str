#pragma once
#ifndef __STR_HPP__
#define __STR_HPP__

class str
{
private:
    char* m_String;
    int m_Length;
    void* m_Address;

    size_t strlen( const char* str )
    {
        const char* char_ptr;
        const unsigned long int* longword_ptr;
        unsigned long int longword, himagic, lomagic;

        for ( char_ptr = str; ( ( unsigned long int ) char_ptr
            & ( sizeof( longword ) - 1 ) ) != 0;
            ++char_ptr )
            if ( *char_ptr == '\0' )
                return char_ptr - str;

        longword_ptr = ( unsigned long int* ) char_ptr;
        himagic = 0x80808080L;
        lomagic = 0x01010101L;

        if ( sizeof( longword ) > 4 )
        {
            himagic = ( ( himagic << 16 ) << 16 ) | himagic;
            lomagic = ( ( lomagic << 16 ) << 16 ) | lomagic;
        }
        if ( sizeof( longword ) > 8 )
            return 0;
        for ( ;;)
        {
            longword = *longword_ptr++;
            if ( ( ( longword - lomagic ) & ~longword & himagic ) != 0 )
            {
                const char* cp = ( const char* )( longword_ptr - 1 );
                if ( cp[ 0 ] == 0 )
                    return cp - str;
                if ( cp[ 1 ] == 0 )
                    return cp - str + 1;
                if ( cp[ 2 ] == 0 )
                    return cp - str + 2;
                if ( cp[ 3 ] == 0 )
                    return cp - str + 3;
                if ( sizeof( longword ) > 4 )
                {
                    if ( cp[ 4 ] == 0 )
                        return cp - str + 4;
                    if ( cp[ 5 ] == 0 )
                        return cp - str + 5;
                    if ( cp[ 6 ] == 0 )
                        return cp - str + 6;
                    if ( cp[ 7 ] == 0 )
                        return cp - str + 7;
                }
            }
        }
    }
public:
    char bytes_table[ 63 ] = { 0x61 /*a*/,0x62 /*b*/,0x63 /*c*/,0x64 /*d*/,0x65 /*e*/,0x66 /*f*/,0x67 /*g*/,0x68 /*h*/,0x69 /*i*/,0x6a /*j*/,0x6b /*k*/,0x6c /*l*/,0x6d /*m*/,0x6e /*n*/,0x6f /*o*/,0x70 /*p*/,0x71 /*q*/,0x72 /*r*/,0x73 /*s*/,0x74 /*t*/,0x75 /*u*/,0x76 /*v*/,0x77 /*w*/,0x78 /*x*/,0x79 /*y*/,0x7a /*z*/,0x41 /*A*/,0x42 /*B*/,0x43 /*C*/,0x44 /*D*/,0x45 /*E*/,0x46 /*F*/,0x47 /*G*/,0x48 /*H*/,0x49 /*I*/,0x4a /*J*/,0x4b /*K*/,0x4c /*L*/,0x4d /*M*/,0x4e /*N*/,0x4f /*O*/,0x50 /*P*/,0x51 /*Q*/,0x52 /*R*/,0x53 /*S*/,0x54 /*T*/,0x55 /*U*/,0x56 /*V*/,0x57 /*W*/,0x58 /*X*/,0x59 /*Y*/,0x5a /*Z*/,0x31 /*1*/,0x32 /*2*/,0x33 /*3*/,0x34 /*4*/,0x35 /*5*/,0x36 /*6*/,0x37 /*7*/,0x38 /*8*/,0x39 /*9*/,0x30 /*0*/,0x0 /**/ };

    str( const char* input_buffer )
    {
        int size = this->strlen( input_buffer ) + 1;
        char* buf = new char[ size ];

        for ( unsigned int i = 0; i < size - 1; i++ )
            buf[ i ] = input_buffer[ i ];

        buf[ size - 1] = '\0';
            
        m_String = buf;
        m_Length = this->strlen( m_String );
        m_Address = &m_String;
    }

    str( char* input_buffer )
    {
        this->m_String = input_buffer;
        this->m_Length = this->strlen( this->m_String );
        this->m_Address = &this->m_String;
    }

    ~str( )
    {
        delete[] this->m_String;
        this->m_Length = 0;
        this->m_Address = nullptr;
    }

    // @ function: Gets the string
    inline char* get( ) const
    {
        return this->m_String;
    }

    bool operator==( const str& s )
    {
        return ( this->m_String == s.get( ) );
    }

    bool operator!=( const str& s )
    {
        return ( this->m_String != s.get( ) );
    }

    // @ function: Converts the string to const char*
    inline const char* get_const( ) const
    {
        return const_cast< char* >( this->m_String );
    }

    // @ function: Gets the length of the string
    inline int& len( ) 
    {
        return this->m_Length;
    }

    // @ function: Checks if the input is in the string
    inline bool contains( char* input )
    {
        if ( !input ) return false;

        int count = 0;
        for ( int i = 0; i < this->m_Length; i++ )
            if ( m_String[ i ] == input[ i ] )
                count++;

        return ( count == this->strlen( input ) );
    }

    // @ function: Checks if the input is in the string
    inline bool contains( const char* input )
    {
        return contains( ( char* )input );
    }

    // @ function: Gets the specified input out of the existing string
    inline char* extract( char* input ) 
    {
        if ( contains( input ) )
        {
            char* buf = new char[ m_Length ];

            for ( int i = 0; i < m_Length; i++ )
                if ( m_String[ i ] == input[ i ] )
                    buf[ i ] = input[ i ];

            for ( int i = 0; i < this->strlen( buf ); i++ )
            {
                if ( buf[ i ] != input[ i ] )
                    buf[ i ] = '\0';              
            }

            return buf;
        }

        return (char* )"";
    }

    // @ function: Gets the specified input out of the existing string
    inline const char* extract( const char* input )
    {
        return const_cast< char* >( extract( ( char* )input ) );
    }
    
    // @ function: Replaces current string wwith new one
    inline char* swap( char* input )
    {
        m_String = input;
        return m_String;
    }

    // @ function: Replaces current string wwith new one
    inline const char* swap( const char* input )
    {
        return const_cast< char* >( swap( ( char* )input ) );
    }

    // @ function: Gets the address of the string
    inline void* addr( ) const
    {
        return m_Address;
    }
    
    // @ function: Gets the address of the index in the string
    inline void* addr_of( const int index ) const
    {
        return reinterpret_cast< void* >( &m_String[ index ] );
    }

    // @ function: Gets all the bytes from the string
    unsigned char* bytes( )
    {
        int& size = m_Length;
        auto out = new unsigned char[ size ];

        for ( unsigned int i = 0; i < size; i++ )
        {
            out[ i ] = reinterpret_cast< unsigned char* >( m_Address )[ i ];
        }

        return out;
    }

    // @ function: Covnerts the buffer (the specified address) into the type.
    template <typename t>
    inline t convert( void* buffer ) const
    {
        return *reinterpret_cast< t* >( reinterpret_cast<void*>(&buffer) );
    }

    // @ function: Performs XOR on the string inputted.
    inline char* xor_encrypt( char* input, char* key )
    {
        char* encrypted = new char[ m_Length + 1 ];

        for ( unsigned int i = 0; i < m_Length; i++ )
            encrypted[ i ] = input[ i ] ^ key[ i % strlen( key ) ];
            
        encrypted[ m_Length ] = '\0';

        return encrypted;
    }

    // @ function: XOR decryption on XOR'ed string.
    inline char* xor_decrypt( char* encrypted, char* key )
    {
        return xor_encrypt( encrypted, key );
    }
};

#endif
