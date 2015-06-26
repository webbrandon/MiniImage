#include <iostream>
#include <sstream>
#include <string>
#include <Magick++.h>

using namespace std;
using namespace Magick;

/* ImageSizeTo Class ********************************************************************************/
class ImageSizeTo
{
    size_t t_height, t_width;
    Image t_image;
    void setFromGeometry( Geometry );

    public:
    // Initializers / Destrucor
    ImageSizeTo( );
    ImageSizeTo( Image & );
    ImageSizeTo( Image &, Geometry );
    ImageSizeTo( Image &, int, int );
    ~ImageSizeTo( );

    // Setters
    void   setSize( int, int );
    void   setSize( Geometry );

    // Getters
    Image  getImage( );
    int    getHeight( );
    int    getWidth( );
    string getSize( );
};
ImageSizeTo::ImageSizeTo( ) : t_width( 0), t_height( 0 ), t_image( Geometry( t_width, t_height ), Color( "rgba( 0, 0, 0, 0 )" ) ) {}
ImageSizeTo::ImageSizeTo( Image & image ) : t_image( image )
{ setFromGeometry( t_image.geometry( ) ); }
ImageSizeTo::ImageSizeTo( Image & image, Geometry geoSize ) : t_image( image )
{ setFromGeometry( geoSize ); }
ImageSizeTo::ImageSizeTo( Image & image, int x, int y ) : t_width( x ), t_height( y ), t_image( image )
{ t_image.resize( Geometry( t_width, t_height ) ); }
ImageSizeTo::~ImageSizeTo( ) { }
void ImageSizeTo::setFromGeometry( Geometry geoSize )
{
    Image image( geoSize, Magick::Color( "rgba( 0, 0, 0, 0 )" ) );
    t_height = image.rows( );
    t_width  = image.columns( );
    t_image.size( Geometry( t_width, t_height ) );
}
Image ImageSizeTo::getImage( )
{ return t_image; }
void  ImageSizeTo::setSize( int x, int y )
{ t_image.resize( Geometry( x, y ) ); }
void  ImageSizeTo::setSize( Geometry geoSize )
{ setFromGeometry( geoSize ); }


/* CommandLine Class ********************************************************************************/
class CommandLine
{
    void setOption( int, int, char **, size_t &, size_t & );
    void setTemplate( Image &, char **, size_t &, size_t & );
    void setOverlay( Image &, char ** );

    public:
    CommandLine( int, char **, Image &, Image &, size_t &, size_t &, size_t &, size_t & );
    ~CommandLine( );
};
CommandLine::CommandLine( int argc, char **argv, Image & tphoto, Image & ophoto, size_t & height, size_t & width, size_t & top, size_t & left )
{
    setTemplate( tphoto, argv, height, width );
    setOverlay( ophoto, argv );
    setOption( 3, argc, argv, top, left );
    setOption( 5, argc, argv, top, left );
}
CommandLine::~CommandLine( ) { }
void CommandLine::setTemplate( Image & photo, char ** argv, size_t & height, size_t & width )
{
    if ( argv[ 1 ] )
    {
        photo.read( argv[ 1 ] );
        height = photo.baseRows( );
        width  = photo.baseColumns( );
    }
    else
        cout << "No template image!" << endl;
}
void CommandLine::setOverlay( Image & photo, char ** argv )
{
    if ( argv[2] )
        photo.read( argv[ 2 ] );
    else
        cout << "No overlay image to process!" << endl;
}
void CommandLine::setOption( int pos, int argc, char ** argv, size_t & top, size_t & left)
{
    if ( argc > pos )
    {
        if ( ( string ) argv[ pos ] == "-t" || ( string ) argv[ pos ] == "--top" )
            top  = atoi( argv[ pos + 1 ] );
        else if ( ( string ) argv[ pos ] == "-l" || ( string ) argv[ pos ] == "--left" )
            left = atoi( argv[ pos + 1 ] );
    }
}


/* Main Functions***********************************************************************************/
void saveImageAsSize( int size, Image & image, size_t height, size_t width )
{
    string sint = static_cast<ostringstream*>( &(ostringstream() << size ) )->str();

    if ( width > (size_t)size || height > (size_t)size )
    {
        ImageSizeTo t_image( image, size, size );
        image = t_image.getImage( );
        image.write( "product-" + sint + "x" + sint + ".png" );
    }
}
void exportToIcons( Image image )
{
    int iconSizes[4] = { 128, 64, 32, 16 };
    for( int i = 0 ; i < sizeof(iconSizes)/sizeof(*iconSizes) ; i++ )
    {
        string sint = static_cast<ostringstream*>( &(ostringstream() << iconSizes[i] ) )->str();
        ImageSizeTo t_image( image, iconSizes[i], iconSizes[i] );
        image = t_image.getImage();
        image.write( "icon-" + sint + "x" + sint + ".ico" );
    }
}
void processSizedImages( Image & image, size_t height, size_t width )
{
    // Save changes to image.
    image.write( "product.png" ); // Orginal template size

    saveImageAsSize( 800, image, height, width );
    saveImageAsSize( 600, image, height, width );
    saveImageAsSize( 400, image, height, width );
    saveImageAsSize( 200, image, height, width );
    saveImageAsSize( 100, image, height, width );
    saveImageAsSize( 50, image, height, width );
}
void prepareImage(Image & tphoto, Image & ophoto, size_t height, size_t width )
{
    const Geometry geoSize( width, height );
    ophoto.size( geoSize );
    tphoto.type( TrueColorMatteType );
    ophoto.type( TrueColorMatteType );
    tphoto.modifyImage( );
    ophoto.modifyImage( );
}
void mergeTemplateOverlay( PixelPacket * tpixels, PixelPacket * opixels, size_t height, size_t width )
{
    Color transparent("rgba(0,0,0,0)");
    for ( size_t row = 0; row <= height ; ++row )
        for ( size_t column = 0 ; column <= width ; ++column )
        {
            if ( ( tpixels->red + tpixels->blue <= 0 ) && tpixels->green >= 255 )
                *tpixels = *opixels;
            *tpixels++;
            *opixels++;
        }
}


/* Main ********************************************************************************************/
int main( int argc, char **argv )
{
    // If compiled for Win or Mac
    InitializeMagick( *argv );

    size_t height = 0, width = 0, top = 0, left = 0;
    Image tphoto, ophoto;
    CommandLine(argc, argv, tphoto, ophoto, height, width, top, left);
    cout << "$ Processing..." << endl;

    prepareImage( tphoto, ophoto, height, width );
    Pixels tview( tphoto );
    Pixels oview( ophoto );
    PixelPacket *tpixels = tview.get( 0, 0, tphoto.columns( ), tphoto.rows( ) );
    PixelPacket *opixels = oview.get( 0, 0, ophoto.columns( ), ophoto.rows( ) );

    mergeTemplateOverlay(tpixels, opixels, height, width);
    tphoto.syncPixels( );
    exportToIcons(tphoto);
    processSizedImages( tphoto, height, width );

    return 0;
}
