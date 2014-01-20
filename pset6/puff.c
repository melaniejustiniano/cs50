/*
 * 
 * Problem Set 6 - Puff
 * Melanie Justiniano
 *
 * Decompresses a huffed file.
 *
 */
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

int main (int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: %s infile outfile \n", argv[0]);
        return 1;
    }
    
    // name files
    char* input = argv[1];
    char* output = argv[2];
    
    // open infile
    Huffile* infile = hfopen(input, "r");
    if (infile == NULL)
    {
        hfclose(infile);
        printf("Could not open %s! \n", input);
        return 1;
    }
    
    // read header
    Huffeader header;
    if (!hread(&header, infile))
    {
        hfclose(infile);
        printf("Could not read header! \n");
        return 1;
    }
    
    // check magic number
    if (header.magic != MAGIC)
    {
        hfclose(infile);
        printf("Not a huffed file! \n");
        return 1;
    }
    
    // check checksum
    int check = 0;    
    for (int i = 0; i < SYMBOLS; i++)
        check += header.frequencies[i];
    
    if (check != header.checksum)
    {
        hfclose(infile);
        printf("Not a huffed file! \n");
        return 1;
    }
    
    // make forest
    Forest* mothafuckinforest = mkforest();
    if (mothafuckinforest == NULL)
    {
        hfclose(infile);
        printf("Could not create forest! \n");
        return 1;
    }
    
    // make and plant trees with non-zero frequency
    for (int i = 0; i < SYMBOLS; i++)
    {
        if (header.frequencies[i] != 0)
        {
            // make tree
            Tree* awyisstree = mktree();
            if (awyisstree == NULL)
            {
                rmforest(mothafuckinforest);
                hfclose(infile);
                printf("Tree could not be created! \n");
                return 1;
            }
            
            // supply tree with information
            awyisstree->symbol = i;
            awyisstree->frequency = header.frequencies[i];
            
            // plant tree
            if (!plant(mothafuckinforest, awyisstree))
            {
                rmtree(awyisstree);
                rmforest(mothafuckinforest);
                hfclose(infile);
                printf("No tree planting up in this house! \n");
                return 1;
            }
        }
    }
    
    // join trees as siblings
    while (mothafuckinforest->first->next != NULL)
    {
        // pick trees for combining
        Tree* treeleft = pick(mothafuckinforest);
        if (treeleft == NULL)
        {
            rmforest(mothafuckinforest);
            hfclose(infile);
            printf("Forest is as barren as your love life. \n");
            return 1;
        }
        Tree* treeright = pick(mothafuckinforest);
        if (treeright == NULL)
        {
            rmforest(mothafuckinforest);
            hfclose(infile);
            printf("Tree could not be picked! \n");
            return 1;
        }

        // make parent tree for joining    
        Tree* bigmommatree = mktree();
        if (bigmommatree == NULL)
        {
            rmtree(bigmommatree);
            rmforest(mothafuckinforest);
            hfclose(infile);
            printf("Could not make tree! \n");
            return 1;
        }
        
        // combine frequencies
        bigmommatree->frequency = treeleft->frequency + treeright->frequency;
        
        // join siblings to parent tree
        bigmommatree->left = treeleft;
        bigmommatree->right = treeright;
        if (!plant(mothafuckinforest, bigmommatree))
        {
            rmtree(bigmommatree);
            rmforest(mothafuckinforest);
            hfclose(infile);
            printf("Tree is having none of this planting shit! \n");
            return 1;
        }
    }
    
    // use last tree
    Tree* treebeard = pick(mothafuckinforest);
    if (treebeard == NULL)
    {
        rmforest(mothafuckinforest);
        hfclose(infile);
        // capitalization to avoid angering Treebeard
        printf("Treebeard the Ent did not want to be picked! \n");
        return 1;
    }
    
    // make cursor that can be changed
    Tree* cursor = treebeard;    
    if (cursor == NULL)
    {
        rmforest(mothafuckinforest);
        hfclose(infile);
        printf("Try navigating that tree now, bitch. \n");
        return 1;
    }
    
    // remove forest
    if (!rmforest(mothafuckinforest))
    {
        hfclose(infile);
        printf("Could not remove forest! \n");
        return 1;
    }
    
    // create and open outfile
    FILE* outfile = fopen(output, "w");
    if (outfile == NULL)
    {
        fclose(outfile);
        printf("Could not open %s! \n", output);
        return 1;
    }
    
    // write file
    int bit;
    
    // read bits from infile
    while ((bit = bread(infile)) != EOF)
    {        
        // move cursor if zero but not if single unique character
        if (bit == 0 && cursor->left != NULL)
        {
            cursor = cursor->left;
        }
        
        // move cursor to right if one
        else if (bit == 1)
        {    
            cursor = cursor->right;
        }
        
        // print symbol at leaf and reset cursor
        if (cursor->left == NULL && cursor->right == NULL)
        {
            if (fprintf(outfile, "%c", cursor->symbol) < 0)
            {
                hfclose(infile);
                fclose(outfile);
                printf("Could not write to %s! \n", output);
                return 1;
            }
            cursor = treebeard;
        }        

    }
    
    // remove tree used for cursor
    rmtree(treebeard);
    
    // close files
    if (!hfclose(infile))
    {
        printf("%s ain't closing. \n", input);
        return 1;
    }
    
    if (fclose(outfile) != 0)
    {
        printf("%s is staying the fuck open. \n", output);
        return 1;
    }
    
    return 0;
}

