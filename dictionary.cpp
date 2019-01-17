/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

typedef struct NodeImplemantation* Node;
struct NodeImplemantation
{
  const char* word;
  Node next;
};
struct DictionaryImplemantation
{
  int length = 0;
  Node head = (Node)malloc(sizeof(struct DictionaryImplemantation));
  Node tail;
  Node iterated;
};
Dictionary new_dictionary ()
{
  Dictionary dict = (Dictionary)malloc(sizeof(struct DictionaryImplemantation));
  dict->head = 0;
  dict->tail = 0;
  return dict;
}

void delete_dictionary (Dictionary dictionary)
{
  Node current = dictionary->head;
  while (current!=0)
  {
    Node deleted_node= current;
    current = current->next;
    sfree(deleted_node);
  }
  sfree(dictionary);
}

void add (Dictionary dict, const char *word)
{
  Node new_word= (Node)malloc(sizeof(struct NodeImplemantation));
  new_word->word = word;
  new_word->next = 0;
  Node current = dict->head;
  if (dict->head == 0)
  {
    dict->head = new_word;
  }
  else
  {
    while (current->next!= 0)
    {
      if (current->word == word)
      {
        return;
      }
      current = current->next;
    }
    current->next = new_word;
  }
  dict->length++;
}

int get_size (Dictionary dict)
{
  return dict->length;
}

bool is_in_dict (Dictionary dict, const char *word)
{
  Node current = dict->head;
  while (current !=0)
  {
    if (strcasecmp(current->word,word) == 0)
    {
      return true;
    }
    current= current->next;
  }
  return false;
}

void start_iterating (Dictionary dict)
{
  dict->iterated = dict->head;
}

bool has_next (Dictionary dict)
{
  return dict->iterated != 0;
}

const char * get_next_entry (Dictionary dict)
{
  if (has_next(dict))
  {
  const char* word = dict->iterated->word;
  dict->iterated = dict->iterated->next;
  return word;
  }
  return 0;
}

void insert_sorted (Dictionary dict, const char *word)
{
  /*new Implementation of insert_sorted*/
  if(is_in_dict(dict, word)) return;

  Node newNode= (Node)malloc(sizeof(struct NodeImplemantation));
  newNode->word = word;
  newNode->next = 0;
  if(dict->head == 0){
    dict->head = newNode;
  }
  else if(dict->head->next == 0){
    if(strcasecmp(dict->head->word, word)>0){
      newNode->next = dict->head;
      dict->head = newNode;
    }
    else
    {
      dict->head->next = newNode;
    }
  }
  else if(strcasecmp(dict->head->word, word)>0)
  {
    newNode->next = dict->head;
    dict->head = newNode;
  }
  else
  {
    Node current = dict->head;
    while(current->next != 0 && strcasecmp(current->next->word, word)<0)
    {
      current = current->next;
    }
    if(current->next == 0){
      dict->length--;
      add(dict, word);
    }
    if(strcasecmp(current->next->word, word)>0){
      newNode->next = current->next;
      current->next = newNode;
    }
  }
  dict->length++;
}
