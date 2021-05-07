#include <vector>
#include <stdexcept>

#include "reversi.h"

using namespace std;

void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}

Square& Square::operator=(SquareValue value)
{
  value_ = value;
  return *this;
}
bool Square::operator==(SquareValue value) const
{
  return (this->value_ == value);
}
bool Square::operator!=(SquareValue value) const
{
  return !(this->value_ == value);
}
std::ostream& operator<<(std::ostream& out, const Square& square)
{
  if(square == Square::FREE)
  {
    out << '-';
  }
  else if(square == Square::WHITE)
  {
    out << 'W';
  }
  else{
    out << 'B';
  }
  return out;
}
//copy constructor for the board
Board::Board(const Board& b)
{
  dimension_ = b.dimension_;
  squares_ = new Square*[b.dimension_];
  for(size_t i = 0; i<dimension_; i++)
  {
    squares_[i] = new Square[b.dimension_];
  }
  for(size_t i = 0; i<dimension_; i++)
  {
    for(size_t j = 0; j<dimension_; j++)
    {
      squares_[i][j] = b.squares_[i][j];
    }
  }
}
//constructor for board class
Board::Board(size_t s)
{
  dimension_ = s;
  squares_ = new Square*[s];
  for(size_t i = 0; i<dimension_; i++)
  {
    squares_[i] = new Square[s];
  }

}
Board::Board()
{
  dimension_ = 0;
  squares_ = NULL;
}
Board::~Board()
{
  for(size_t i = 0; i<dimension_; i++)
  {
    delete[] squares_[i];
  }
  delete[] squares_;
}

Board& Board::operator=(const Board& rhs)
{
  //deep copy constructor of the board class
  if(this == &rhs)
  {
    return *this;
  }
  if(squares_ != NULL)
  {
    for(size_t i = 0; i<dimension_; i++)
    {
      delete[] squares_[i];
    }
    delete[] squares_;
  }
  dimension_ = rhs.dimension_;
  squares_ = new Square*[rhs.dimension_];
  for(size_t i = 0; i<rhs.dimension_; i++)
  {
     squares_[i] = new Square[rhs.dimension_];
  }

  for(size_t i = 0; i<dimension_; i++)
  {
    for(size_t j = 0; j<dimension_; j++)
    {
      squares_[i][j] = rhs.squares_[i][j];
    }
  }
  return *this;
}

Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}
Board& Board::flip_one(char row, size_t column, Square::SquareValue turn)
{
  squares_[row_to_index(row)][column-1] = turn;
  return (*this);
}
//accessor function to flip the squares
Board& Board::flip_squares(char row, size_t column, Square::SquareValue turn)
{
  // Vectors for each cardinal direction
  const size_t direction_count = 8;
  const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
  const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

  //check in every direction
  for (size_t d = 0; d < direction_count; d++)
  {
      // Where we're checking
      char cursor_row = row + direction_row[d];
      size_t cursor_column = column + direction_column[d];

      // Move towards the direction
      //this will break when we encounter out same color or a free square
      while (is_legal_and_opposite_color(cursor_row, cursor_column, turn))
      {
          cursor_row += direction_row[d];
          cursor_column += direction_column[d];
      }

      // Check if the next thing after is our color
      bool found_same = is_legal_and_same_color(cursor_row, cursor_column, turn);
      // If this direction is valid, the move is valid, so short circuit and return
      if(found_same == true)
      {
        cursor_row -= direction_row[d];
        cursor_column -= direction_column[d];
        while(is_legal_and_opposite_color(cursor_row, cursor_column, turn))
        {
          flip_one(cursor_row, cursor_column, turn);
          cursor_row -= direction_row[d];
          cursor_column -= direction_column[d];
        }
        flip_one(cursor_row, cursor_column, turn);
      }
  }
  return *this;
}
Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn)
{
  board_ = b;
  turn_ = turn;
}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
  board.print(out);
  return out;
}

//constructs the board and specifies the initial turn,
//which is black
Reversi::Reversi(size_t size)
{
  //deep copy of the board
  Board b(size);
  board_ = b;
  turn_ = Square::BLACK;

  board_ = board_.flip_one('a' + size/2 - 1, size/2, Square::BLACK);
  board_ = board_.flip_one('a' + size/2, size/2 + 1, Square::BLACK);
  board_ = board_.flip_one('a' + size/2, size/2, Square::WHITE);
  board_ = board_.flip_one('a' + size/2 - 1, size/2 + 1, Square::WHITE);
}
void Reversi::play()
{
  //first need to prompt the board and initialize gameplay
  bool playing = true;
  char initial;

  cout << endl;
  cout << "Welcome to the board game Reversi! Select p r/c to choose your square. Select q to exit the program. "; 
  cout << "Select c to save this checkpoint. Select u to go back to your previously saved checkpoint. Good luck!" << endl;

  while(playing)
  {
    prompt();
    cin >> initial;

    if(initial == 'p')
    {
      char row;
      size_t col;
      cin >> row >> col;
      if(is_legal_choice(row, col, turn_))
      {
        board_ = board_.flip_squares(row, col, turn_);
        turn_ = opposite_color(turn_);
      }
      else{
        turn_ = opposite_color(turn_);
      }

    }
    else if(initial == 'c')
    {
      save_checkpoint();
    }
    else if(initial == 'u')
    {
      undo();
    }
    //exit the program for q
    else if(initial == 'q')
    {
      size_t white_count = player_count(Square::WHITE);
      size_t black_count = player_count(Square::BLACK);
      win_loss_tie_message(white_count, black_count);
      playing = false;
    }
    //if the user enters anything else immediately quit the program
    else{
      size_t white_count = player_count(Square::WHITE);
      size_t black_count = player_count(Square::BLACK);
      win_loss_tie_message(white_count, black_count);
      playing = false;
    }
  }
}
//this is correct
void Reversi::save_checkpoint()
{
  Checkpoint check(board_, turn_);
  history_.push_back(check);
}
void Reversi::undo()
{
  //if there isnt a history then do nothing
  if(history_.empty())
  {
    return;
  }
  //need to perform a deep copy
  board_ = history_.back().board_;
  turn_ = history_.back().turn_;
  //board should be deleted by the destructor in the board class
  //need to delete the last checkpiont in the vector
  history_.pop_back();
}


void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if(board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);
        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}
//function that returns the players count as type size_t
size_t Reversi::player_count(Square::SquareValue turn)
{
  size_t count = 0;
  for(unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
  {
    for(size_t col = 1; col <= board_.dimension(); col++)
    {
      if(board_(row,col) == turn)
      {
        count++;
      }
    }
  }
  return count;
}
