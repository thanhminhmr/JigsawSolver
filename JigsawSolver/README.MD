# JigsawSolver

Thư mục chứa mã nguồn đang phát triển.

## Cấu trúc thư mục

| Tên tệp | Chức năng |
| --- | --- |
| main.cpp | Chứa chương trình chính |
| Point.h | Chứa một điểm |
| Vector.h | Chứa một véc-tơ quay |
| Angle.h | Chứa một góc, tạo thành bởi 2 véc-tơ quay |
| Piece.h | Chửa một mảnh ghép, là danh sách các điểm và các góc theo chiều kim đồng hồ |
| Board.h | Chứa một tập các mảnh ghép, là danh sách các chỗ trống còn lại trên bàn (hoặc là toàn bộ chỗ trống trên bàn) |
| misc.h | Chứa các hàm dùng chung của chương trình |
| std.h | Chứa thư viện chuẩn, các cấu trúc dữ liệu chương trình |

## Phương án phát triển

### Phương án xếp chung:

1. Đọc và lưu trữ Piece.
2. Xoay và lật các Piece theo tất cả các hướng, nhận đc tập hợp các vị trí có thể của Piece.
3. Chọn góc bé nhất của Board, tìm các cách xếp các Piece vào vị trí đó thoả mãn cách xếp là hợp lệ, nếu không có cách xếp hợp lệ thì quay lui.
4. Với mỗi cách xếp, nếu Board bị chia làm 2 phần, chọn phần có diện tích bé hơn.
5. Với Board (hoặc mỗi phần của Board), quay lại bước 3, hoặc dừng lại khi tìm thấy cách xếp đúng.

