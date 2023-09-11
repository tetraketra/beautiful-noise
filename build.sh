FILES=$(find ./src/*.c -type f | tr -s '\n' ' ')
WARNS="-W -Wextra -Wno-multichar -Wall"
LINKS="-lSDL2 -lSDL2_ttf -std=gnu2x"
DEBUG="-g3"
FNAME="beautiful-noise"

echo "Executing with..."
echo "FILES: $FILES"
echo "WARNS: $WARNS"
echo "LINKS: $LINKS"
echo "DEBUG: $DEBUG"

echo "Counting..."
find ./ -type f \( -iname \*.c -o -iname \*.h \) \
    | xargs wc -l \
    | sort -nr


gcc $FILES -o ./bin/$FNAME $WARNS $LINKS $DEBUG -ftime-report \
    > tmp.txt 2>&1

echo "Reporting..."
cat tmp.txt \
    | grep -E --color=never '^(Time variable| [[:alnum:]])' \
    | cut -c1-36,69-79 \
    | sed 's/   wall/ /' \
    | awk -v list="$FILES" 'BEGIN { file_index=1 }
        {
            if (gsub("Time variable", (file_index <= split(list, arr) ? arr[file_index] : "File"))) {
                file_index = (file_index < length(arr) ? file_index + 1 : 1)
            }
            print
        }'

echo "Building..."
cat tmp.txt \
    | grep -v -E '^(Time variable| [[:alnum:]])' \
    | grep -v '^$'

rm tmp.txt

chmod a+x ./bin/$FNAME
echo "Execute ./bin/$FNAME to start $FNAME."
